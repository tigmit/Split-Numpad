/**
 * main.cpp
 * brief   : main compilation unit containing loop and setup
 * created : 21.07.2024
 * creator : @tigmit Licence : opensource
 */

#include "FSM.hpp"
#include "Model.hpp"
#include <Arduino.h>

// setup Task handles
TaskHandle_t Loop0; // loop running on core 0
TaskHandle_t Loop1; // loop running on core 1 (default core)
void Loop1_(void *param);
void Loop0_(void *param);

FSM fsm; // start with default state -> pStartUp

void setup() {
  Serial.begin(serialBaudRate);

  //______________________ initialize dependencies

  // init keyboard Handler
  kbdHandler.init();
  // init Display Handler
  dspHandler.init();
  // init encoder Handler
  encHandler.init();
  // init rgbHandler
  rgbHandler.init();

  // creating loop on core 1 (default core)
  xTaskCreatePinnedToCore(Loop0_, "Loop0", 10000, NULL, 0, &Loop0, 0);
  // creating loop on core 0
  xTaskCreatePinnedToCore(Loop1_, "Loop1", 10000, NULL, 1, &Loop1, 1);
  Serial.println("cores initialized");
}

void Loop0_(void *param) {
  fsm.startup();
  while (true) {
    fsm.update();
  }
}

void Loop1_(void *param) { // explicitly for scanning the btn matrix
  // setup section for loop1:
  //______________________RUN Loop1 (default core)
  while (true) {
    kbdHandler.updateKeyMatrix();
  }
}

// nothing to do here
void loop() {}
