/*
  xsns_80_mfrc522.ino - Support for MFRC522 (SPI) NFC Tag Reader on Tasmota

  Copyright (C) 2020  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef USE_RC522
/*********************************************************************************************\
 * MFRC522 - 13.56 MHz RFID reader
 *
 * Connections:
 * MFRC522  ESP8266         Tasmota
 * -------  --------------  ----------
 *  SDA     GPIO0..5,15,16  SPI CS
 *  SCK     GPIO14          SPI CLK
 *  MOSI    GPIO13          SPI MOSI
 *  MISO    GPIO12          SPI MISO
 *  IRQ     not used
 *  Gnd     Gnd
 *  Rst     GPIO0..5,15,16  RC522 Rst
 *  3V3     3V3
\*********************************************************************************************/

#define XSNS_80        80

#define USE_RC522_DATA_FUNCTION

#include <MFRC522.h>
MFRC522 *Mfrc522;

struct RC522 {
  char uids[21];           // Number of bytes in the UID. 4, 7 or 10
  bool present = false;
  uint8_t scantimer = 16;
} Rc522;

void RC522ScanForTag(void) {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  if (!Mfrc522->PICC_IsNewCardPresent() || !Mfrc522->PICC_ReadCardSerial()) { return; }

  ToHex_P((unsigned char*)Mfrc522->uid.uidByte, Mfrc522->uid.size, Rc522.uids, sizeof(Rc522.uids));

  MFRC522::PICC_Type piccType = Mfrc522->PICC_GetType(Mfrc522->uid.sak);
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("MFR: UID %s, Type %s"), Rc522.uids, Mfrc522->PICC_GetTypeName(piccType));

#ifdef USE_RC522_DATA_FUNCTION
  bool didit = false;
  if (   piccType == MFRC522::PICC_TYPE_MIFARE_MINI
      || piccType == MFRC522::PICC_TYPE_MIFARE_1K
      || piccType == MFRC522::PICC_TYPE_MIFARE_4K) {

    uint8_t trailerBlock = 7;
    MFRC522::MIFARE_Key key;
    for (uint32_t i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF;
    }
    MFRC522::StatusCode status = Mfrc522->PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(Mfrc522->uid));
    if (status == MFRC522::STATUS_OK) {
      uint8_t buffer[18];  // The buffer must be at least 18 bytes because a CRC_A is also returned
      uint8_t size = sizeof(buffer);
      status = (MFRC522::StatusCode) Mfrc522->MIFARE_Read(1, buffer, &size);
      if (status == MFRC522::STATUS_OK) {
        char card_datas[34];
        for (uint32_t i = 0; i < size -2; i++) {
          if ((isalpha(buffer[i])) || ((isdigit(buffer[i])))) {
            card_datas[i] = char(buffer[i]);
          } else {
            card_datas[i] = '\0';
          }
        }
        didit = true;
        ResponseTime_P(PSTR(",\"RC522\":{\"UID\":\"%s\",\"" D_JSON_DATA "\":\"%s\"}}"), Rc522.uids, card_datas);
      }
    }
  }
  if (!didit) {
    ResponseTime_P(PSTR(",\"RC522\":{\"UID\":\"%s\"}}"), Rc522.uids);
  }
#else
  ResponseTime_P(PSTR(",\"RC522\":{\"UID\":\"%s\"}}"), Rc522.uids);
#endif
  MqttPublishTeleSensor();

  // Halt PICC
  Mfrc522->PICC_HaltA();

  Rc522.scantimer = 7;  // Ignore tags found for two seconds
}

void RC522Init(void) {
  if (PinUsed(GPIO_SPI_CS) && PinUsed(GPIO_RC522_RST)) {
    Mfrc522 = new MFRC522(Pin(GPIO_SPI_CS), Pin(GPIO_RC522_RST));
    SPI.begin();
    Mfrc522->PCD_Init();
    if (Mfrc522->PCD_PerformSelfTest()) {
      uint8_t v = Mfrc522->PCD_ReadRegister(Mfrc522->VersionReg);
      char ver[8] = { 0 };
      switch (v) {
        case 0x92: strcpy_P(ver, PSTR("v2.0")); break;
        case 0x91: strcpy_P(ver, PSTR("v1.0")); break;
        case 0x88: strcpy_P(ver, PSTR("clone")); break;
        case 0x00: case 0xFF: strcpy_P(ver, PSTR("fail")); break;
      }
      uint8_t empty_uid[4] = { 0 };
      ToHex_P((unsigned char*)empty_uid, sizeof(empty_uid), Rc522.uids, sizeof(Rc522.uids));
      AddLog_P(LOG_LEVEL_INFO, PSTR("MFR: RC522 Rfid Reader detected %s"), ver);
      Rc522.present = true;
    }
  }
}

#ifdef USE_WEBSERVER
void RC522Show(void) {
  WSContentSend_PD(PSTR("{s}RC522 UID{m}%s {e}"), Rc522.uids);
}
#endif  // USE_WEBSERVER

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xsns80(uint8_t function) {
  bool result = false;

  if (FUNC_INIT == function) {
    RC522Init();
  }
  else if (Rc522.present) {
    switch (function) {
      case FUNC_EVERY_250_MSECOND:
        if (Rc522.scantimer) {
          Rc522.scantimer--;
        } else {
          RC522ScanForTag();
        }
        break;
#ifdef USE_WEBSERVER
      case FUNC_WEB_SENSOR:
        RC522Show();
        break;
#endif  // USE_WEBSERVER
    }
  }
  return result;
}

#endif  // USE_RC522
