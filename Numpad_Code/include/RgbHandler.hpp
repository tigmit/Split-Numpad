/**
 * ../lib/RgbHandler.hpp
 * brief   : this class handles all the tasks to controll the pixel LEDs.
 * created : 13.06.2024
 * creator : @tigmit Licence : opensource
 */

#pragma once
#include "layout.hpp"

#include <EEPROM.h>
#include <FastLED.h>

class Config {
public:
  friend class RgbHandler;

  Config() = default;

  Config operator=(Config newConfig) {
    this->rgbConfig_.rgbOn = newConfig.rgbConfig_.rgbOn;
    this->rgbConfig_.currentBrightness = newConfig.rgbConfig_.currentBrightness;
    this->rgbConfig_.currentRGBValue = newConfig.rgbConfig_.currentRGBValue;
    this->rgbConfig_.rVal = newConfig.rgbConfig_.rVal;
    this->rgbConfig_.gVal = newConfig.rgbConfig_.gVal;
    this->rgbConfig_.bVal = newConfig.rgbConfig_.bVal;
    return *this;
  }

  void storeConfigToEEPROM() {
    EEPROM.begin(EEPROMSize); // begin transfer
#ifdef EEPROM_LOG
    Serial.println("transfer current config to EEPROM");
    printConfigBytesInEEPROM(false);
#endif
    EEPROM.put(configEEPROMAdress, rgbConfig_);
    EEPROM.commit();
#ifdef EEPROM_LOG
    Serial.println("confirm new Config : ");
    printConfigBytesInEEPROM(false);
#endif
    EEPROM.end(); // end transfer
  }

  void transferConfigfromEEPROM() {
    EEPROM.begin(EEPROMSize);
    EEPROM.get(configEEPROMAdress, rgbConfig_); // data passed by refference
#ifdef EEPROM_LOG
    Serial.println("transfered Config form flash to current config in stack");
    printConfigBytesInEEPROM(false); // begin read
#endif
    EEPROM.end(); // end read
  }

  bool isOccupied() {
    EEPROM.begin(EEPROMSize); // begin read
    for (int i = configEEPROMAdress; i < configEEPROMAdress + EEPROMSize; i++) {
      if (EEPROM.read(i) != (uint8_t)0xFF) {
        EEPROM.end();
#ifdef EEPROM_LOG
        Serial.println("FOUND config in EEPROM");
#endif
        return true;
      }
    }
#ifdef EEPROM_LOG
    Serial.println("EEPROM is empty");
#endif
    EEPROM.end(); // end read
    return false;
  }

  void clearEEPROM() {
    EEPROM.begin(EEPROMSize); // begin read
    for (int i = configEEPROMAdress; i < configEEPROMAdress + EEPROMSize; i++) {
      EEPROM.write(i, (uint8_t)0xFF);
#ifdef EEPROM_LOG
      Serial.print("BYTE at ");
      Serial.print(i);
      Serial.println("set to 0xFF");
#endif
    }
#ifdef EEPROM_LOG
    Serial.println("confirm cleared");
    printConfigBytesInEEPROM(false);
#endif
    EEPROM.end(); // end read
  }

  void printConfigBytesInEEPROM(bool newSession = true) {
    if (newSession) {
      EEPROM.begin(EEPROMSize); // begin read
    }
    Serial.print("  printing EEPROM content starting at Adress : ");
    Serial.println(configEEPROMAdress);
    Serial.print("  ");
    for (int i = configEEPROMAdress; i < configEEPROMAdress + EEPROMSize; i++) {
      Serial.print(EEPROM.read(i), HEX);
      Serial.print(" ");
    }
    Serial.println(" ");
    if (newSession) {
      EEPROM.end(); // end read
    }
  }

private:
  const size_t EEPROMSize{10};     // Bytes
  const int configEEPROMAdress{0}; // store at adress 0

  // __attribute ((packed)) wont work here because i want to store CRGB
  struct rgbConfig {
    bool rgbOn = true;
    uint8_t currentBrightness = 0xFF;
    CRGB currentRGBValue = CRGB::Aqua;
    uint8_t rVal = currentRGBValue[0];
    uint8_t gVal = currentRGBValue[1];
    uint8_t bVal = currentRGBValue[2];
  };
  // this is the config we actually want to store in EEPROM
  rgbConfig rgbConfig_;
};

class RgbHandler {
public:
  RgbHandler() = default;

  void init() {
    if (currentConfig.isOccupied()) {
      // EEPROM contains a config. load it
      currentConfig.transferConfigfromEEPROM();
    } else {
      currentConfig.storeConfigToEEPROM(); // store the default config
    }

    FastLED.addLeds<NEOPIXEL, LedControllPin>(leds, numLeds);
    FastLED.setBrightness(currentConfig.rgbConfig_.currentBrightness);
    // use this to limit the current draw from the lipo
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 800);

    for (int i = 0; i < numLeds; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

  void setConstColor(CRGB color) {
    for (int i = 0; i < numLeds; i++) {
      leds[i] = color;
    }
    FastLED.show();
  }

  void setBrightnes(u_int8_t val) {
    FastLED.setBrightness(val);
    FastLED.show();
  }

  void startupSequence() {
    FastLED.setBrightness(currentConfig.rgbConfig_.currentBrightness);
    for (int i = 0; i < numLeds; i++) {
      leds[i] = CRGB::Purple;
      FastLED.show();
      delay(12); // boot animation time between leds
    }
    if (currentConfig.rgbConfig_.rgbOn) {
      setConstColor(currentConfig.rgbConfig_.currentRGBValue);
    } else {
      turnRgbOff();
    }
  }

  void turnRgbOff() {
    setConstColor(CRGB::Black);
    currentConfig.rgbConfig_.rgbOn = false;
  }
  void turnRgbOn() {
    setConstColor(currentConfig.rgbConfig_.currentRGBValue);
    currentConfig.rgbConfig_.rgbOn = true;
  }

  void pushCurrentRGBValues() {
    currentConfig.rgbConfig_.currentRGBValue[0] = currentConfig.rgbConfig_.rVal;
    currentConfig.rgbConfig_.currentRGBValue[1] = currentConfig.rgbConfig_.gVal;
    currentConfig.rgbConfig_.currentRGBValue[2] = currentConfig.rgbConfig_.bVal;
    setConstColor(currentConfig.rgbConfig_.currentRGBValue);
    currentConfig.rgbConfig_.rgbOn = true;
  }

  void pushcurrentBrightness() {
    FastLED.setBrightness(currentConfig.rgbConfig_.currentBrightness);
    FastLED.show();
    currentConfig.rgbConfig_.rgbOn = true;
  }

  void pushSingleRGB(int8_t row, int8_t coll, CRGB color = CRGB::Black) {
    if (rgbLayout[row][coll] == rgbNC) {
      Serial.println("WARNING : pushSingleRGB() LED NOT CONNECTED IN MATRIX");
      Serial.print("Row : ");
      Serial.print(row);
      Serial.print(" | col : ");
      Serial.println(coll);
      Serial.println("no further action. NO LEDs were set");
      return;
    } else if (color != CRGB::Black) {
      leds[rgbLayout[row][coll]] = color;
    } else {
      // providing no color value will resort to the config value
      leds[rgbLayout[row][coll]] = currentConfig.rgbConfig_.currentRGBValue;
    }
    FastLED.setBrightness(currentConfig.rgbConfig_.currentBrightness);
    FastLED.show();
  }

  bool rgbIsOn() const { return currentConfig.rgbConfig_.rgbOn; }

  uint8_t &getRval() { return currentConfig.rgbConfig_.rVal; }
  uint8_t &getGval() { return currentConfig.rgbConfig_.gVal; }
  uint8_t &getBval() { return currentConfig.rgbConfig_.bVal; }
  uint8_t &getCurrentBrightness() {
    return currentConfig.rgbConfig_.currentBrightness;
  }

  uint8_t getMaxRgbBrightness() const { return maxRgbBrightness; }
  Config &getCurrentConfig() { return currentConfig; }

private:
  // Max brightness for white Whithout display flickler
  const uint8_t maxRgbBrightness = 0x1E;

  // Define the array of leds
  CRGB leds[numLeds];

  Config currentConfig;
};