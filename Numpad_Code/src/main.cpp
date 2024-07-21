/**
 * main.cpp
 * brief   : main compilation unit containing loop and setup
 * created : 21.07.2024
 * creator : @tigmit Licence : opensource
 */

#include "keyBoardHandler.hpp"
#include <Arduino.h>

// setup Task handles
TaskHandle_t Loop0; // loop running on core 0
TaskHandle_t Loop1; // loop running on core 1 (default core)
void Loop1_(void *param);
void Loop0_(void *param);

// init keyboard handler
KeyboardHandler kbdHandler;

void setup() {
  Serial.begin(115200);

  // creating loop on core 1 (default core)
  xTaskCreatePinnedToCore(Loop0_, "Loop0", 10000, NULL, 0, &Loop0, 0);
  // creating loop on core 0
  xTaskCreatePinnedToCore(Loop1_, "Loop1", 10000, NULL, 1, &Loop1, 1);
  Serial.println("cores initialized");

  //______________________ initialize dependencies

  kbdHandler.init();
}

void Loop0_(void *param) {
  while (true) {
    delay(1); // TODO: this core will handle display tasks. we need to do
              // something in here otherwise the MCU will crash...
              // therefore. delay a random ammount.
  }
}

void Loop1_(void *param) { // explicitly for scanning the btn matrix
  // setup section for loop1:
  //__________________RUN Loop1 (default core)
  while (true) {
    kbdHandler.updateKeyMatrix();
  }
}

// nothing to do here
void loop() {}
