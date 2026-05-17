// STM32 Blue Pill SPI LCD Example
// Simulation: https://wokwi.com/projects/374780854731040769

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_SCK 4
#define TFT_MOSI 6
#define TFT_DC 1
#define TFT_CS 3
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#include "FS.h"
#include "SD.h"
#define pinCS 10
#define pinSI 6
#define pinSO 5
#define pinSK 4

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\t SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Wokwi mBusMiniC3 SPI LCD/SdCard w/ LED Blinking...");
  //LCD-----------------------------------
  tft.begin();
  tft.setCursor(50, 140);
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(2);
  tft.println("mBusMiniC3");
  tft.setCursor(60, 180);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.println("Hello!");
  //SD card---------------------------------
  SPI.begin(pinSK, pinSO, pinSI, pinCS);
  if (!SD.begin(pinCS)) {
    Serial.println("Card Mount Failed");
    return;
    }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
    }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
    }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  listDir(SD, "/", 0);
  Serial.printf("Total space:\t %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space:\t %lluKB\n", SD.usedBytes()/1024);
  //LED------------------------------------
  pinMode(0, OUTPUT);
}

void loop() {
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  delay(500);
}