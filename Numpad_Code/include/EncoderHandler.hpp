/**
 * ../lib/EncoderHandler.hpp
 * brief   : this class handles all the tasks required to read the rotary
 * encoder created : 25.05.2024 creator : @tigmit Licence : opensource
 */
#pragma once

#include "hardwareDef.hpp"
#include <Arduino.h>
#include <ESP32Encoder.h> // https://github.com/madhephaestus/ESP32Encoder.git
#include <math.h>

class EncoderHandler {
public:
  EncoderHandler() = default;

  void init() {
    encoder.attachHalfQuad(encDT, encCLK);
    encoder.setCount(0);
    pinMode(encBTN, INPUT);
  }

  bool EncButtonPressed() {
    // check if the button was pressed
    int reading = digitalRead(encBTN);

    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == LOW) {
          return true;
        }
      }
    }
    lastButtonState = reading;
    return false;
  }

  long getEncPos() { // depricated... dead code wiil delete
    encoderPosition = encoder.getCount() / 2;
    return encoderPosition;
  }

  uint8_t updateMainMenueSelect() {
    encoderPosition = encoder.getCount() / 2;
    if (encoderPosition) {
      // mainMenueSelect += (encoderPosition > 0) ? 1 : -1;
      if (encoderPosition > 0) { // pos
        mainMenueSelect++;
        mainMenueSelect %= 5; // this is the number of menue items
      } else {                // neg
        mainMenueSelect = (mainMenueSelect == 0) ? 3 - 1 : mainMenueSelect - 1;
      }

      encoder.clearCount();
      // TODO: need to define number of menue items
      // lets say num items == 3
    }
    return mainMenueSelect;
  }

private:
  ESP32Encoder encoder;

  long encoderPosition = 0;

  // button
  int buttonState;
  int lastButtonState = HIGH;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 50;

  // menue selectors
  uint8_t mainMenueSelect{0};
};
