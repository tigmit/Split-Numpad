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
    display.clearDisplay();
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

  void setCursor(int16_t x = 20, int16_t y = 20, uint8_t textSize = 1) {
    display.setTextSize(textSize); // Normal 1:1 pixel scale
    display.setCursor(x, y);       // start line at x,y
    display.cp437(true);           // Use full 256 char 'Code Page 437' font
    display.setTextColor(SSD1306_WHITE); // Draw white text
  }

  void pushBitmap(const uint8_t *bmp, const uint8_t w, const u_int8_t h,
                  uint8_t x = 10, uint8_t y = 10, bool clear = true) {
    // for center use
    //(display.width() - w) / 2 for x
    //(display.height() - h) / 2 for y
    assert(((x + w) <= SCREEN_WIDTH) && "WARNING: BMP width out of bounds");
    assert(((y + h) <= SCREEN_HEIGHT) && "WARNING: BMP Height out of bounds");
    if (clear) {
      clearSection(x, y, w, h);
    }
    display.drawBitmap(x, y, bmp, w, h, 1);
    display.display();
  }

  void PushLine(uint8_t x = 0, uint8_t y = 10, uint8_t w = 128,
                bool clear = true) {
    if (clear) {
      display.clearDisplay();
    }
    display.drawFastHLine(x, y, w, SSD1306_WHITE);
    display.display();
  }

  void clearSection(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    display.fillRect(x, y, w, h, 0);
    display.display();
  }

  template <typename T> void operator<<(T data) { display.write(data); }

  void clear(bool push = false) {
    display.clearDisplay();
    if (push) {
      display.display();
    }
  }
  void push() { display.display(); }

private:
  Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET};
};
