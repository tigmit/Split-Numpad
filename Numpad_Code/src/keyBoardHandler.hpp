/**
 * KeyboardHandler.hpp
 * brief   : this class handles all the tasks of the keymatrix such as scanning
 *           inputs and initializing the array
 * created : 21.07.2024
 * creator : @tigmit Licence : opensource
 */
#pragma once
#include "hardwareDef.hpp"

#include "debugSettings.hpp"
#include "layout.hpp"
#include <BleKeyboard.h>

BleKeyboard kbd("tigmit_Numpad", "tigmit", 100);
class KeyboardHandler {
public:
  KeyboardHandler() = default;

  /**
   * @brief initialize all the row pins
   * @return void
   * @param none
   */
  void init() {

    // Initialize row INPUT pin and set default state
    for (int i = 0; i < numRows; i++) {
      pinMode(rows[i], INPUT_PULLDOWN);
    }
    for (int i = 0; i < numCols; i++) {
      pinMode(colls[i], OUTPUT);
    }

    kbd.begin();
    Serial.println("Keypad initialized wait for BLE Connect.");

    // setup BLE connection indicator LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
  }

  /**
   * @brief scanning each key and listening for keypresses
   * @return void
   * @param none
   */
  void updateKeyMatrix() {
    // if we are not connected we don't do anything here
    if (!kbd.isConnected())
      return;

    //_______________________________________________________set colls
    for (int colIdx = 0; colIdx < numCols; colIdx++) {
      digitalWrite(colls[colIdx], HIGH);
      // giving the I/Os some time to get a stable output
      delayMicroseconds(outputSetDelay);

      //_____________________________________________________scan Rows
      for (int rowIdx = 0; rowIdx < numRows; rowIdx++) {
        if (digitalRead(rows[rowIdx]) && !pressed[layerIdx][rowIdx][colIdx]) {
#ifndef DISABLE_BLE_OUTPUT
          kbd.press(layout1[layerIdx][rowIdx][colIdx]);
#endif
          pressed[layerIdx][rowIdx][colIdx] = ON;

#ifdef DEBUG_LVL_1
          Serial.print("key pressed : rowIDX : ");
          Serial.print(rowIdx);
          Serial.print(" | colIDX : ");
          Serial.print(colIdx);
          Serial.print(" | pressed : ");
          Serial.print(pressed[layerIdx][rowIdx][colIdx]);
          Serial.println(" ");
#endif

        } else if (!digitalRead(rows[rowIdx]) &&
                   pressed[layerIdx][rowIdx][colIdx]) {

#ifndef DISABLE_BLE_OUTPUT
          kbd.release(layout1[layerIdx][rowIdx][colIdx]);
#endif
          pressed[layerIdx][rowIdx][colIdx] = OFF;
#ifdef DEBUG_LVL_1
          Serial.print("key RELEASED: rowIDX : ");
          Serial.print(rowIdx);
          Serial.print(" | colIDX : ");
          Serial.print(colIdx);
          Serial.print(" | pressed : ");
          Serial.print(pressed[layerIdx][rowIdx][colIdx]);
          Serial.println(" ");
#endif
        }
      }
      digitalWrite(colls[colIdx], LOW);
    }
  }

  bool getKeyPressToggle() const { return keyPressToggle; }

private:
  bool keyPressToggle = false;
  uint32_t outputSetDelay = 100; // µSeconds

  // NOTE: once i introduce Layers this is used to toggle these layers
  int layerIdx = 0;
};
