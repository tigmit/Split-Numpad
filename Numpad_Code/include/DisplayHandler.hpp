/**
 * ../lib/DisplayHandler.hpp
 * brief   : this class capsulates all tasks related to the display.
 * created : 07.09.2024
 * creator : @tigmit Licence : opensource
 */

#pragma once
#include "hardwareDef.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

class DisplayHandler {
public:
  DisplayHandler() = default;

  void init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      Serial.println(F("Display is depricated"));
    } else {
      Serial.println(F("SSD1306 allocation success"));
    }
  }

  void pushExample() {
    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds
    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    display.drawPixel(10, 10, SSD1306_WHITE);
    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);
  }

private:
  Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET};
};
