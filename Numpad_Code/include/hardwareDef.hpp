/**
 * hardwareDef.hpp
 * brief   : defining the pins for the key matrix
 * created : 21.07.2024
 * creator : @tigmit
 * Licence : opensource
 */
#pragma once
#include <Arduino.h>

// Define on and off values
constexpr bool OFF{0};
constexpr bool ON{1};

// Defines for keymatrix:
// set these based on your keymatrix setup
constexpr uint8_t row0{26};
constexpr uint8_t row1{25};
constexpr uint8_t row2{33};
constexpr uint8_t row3{32};
constexpr uint8_t row4{35};

constexpr uint8_t coll0{27};
constexpr uint8_t coll1{14};
constexpr uint8_t coll2{12};
constexpr uint8_t coll3{13};

// battery is charging indicator
// TBD

// reading the battery voltage through 33k / 100k voltage devider
// TBD

// Matrix setup
constexpr uint8_t numRows{5};
constexpr uint8_t numCols{4};
constexpr uint8_t numLayers{1};

// pins for rotary Encoder
//#define encCLK 17  // CLK ENCODER    TBD
//#define encDT  16  // DT ENCODER     TBD
//#define encBTN 39  // encoder button TBD
