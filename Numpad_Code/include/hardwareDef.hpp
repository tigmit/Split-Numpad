/**
 * hardwareDef.hpp
 * brief   : defining the pins for the key matrix
 * created : 21.07.2024
 * creator : @tigmit
 * Licence : opensource
 */
#pragma once
#include <Arduino.h>

// Defines for keymatrix:
constexpr uint8_t row0{26}; // tbd
constexpr uint8_t row1{25}; // tbd
constexpr uint8_t row2{33}; // tbd
constexpr uint8_t row3{32}; // tbd
constexpr uint8_t row4{35}; // tbd

constexpr uint8_t coll0{27}; // tbd
constexpr uint8_t coll1{14}; // tbd
constexpr uint8_t coll2{12}; // tbd
constexpr uint8_t coll3{13}; // tbd

// Matrix dimentions
constexpr uint8_t numRows{5};
constexpr uint8_t numCols{4};
constexpr uint8_t numLayers{1};

// Define on and off values
constexpr bool OFF{0};
constexpr bool ON{1};

// Display Defines
constexpr uint8_t SCREEN_WIDTH{128}; // OLED display width, in pixels
constexpr uint8_t SCREEN_HEIGHT{64}; // OLED display height, in pixels
constexpr int8_t OLED_RESET{-1};     // Reset pin (-1 if sharing default reset)
constexpr uint8_t SCREEN_ADDRESS{0x3C}; // datasheet for refference

// pins for rotary Encoder
// #define encCLK 17  // CLK ENCODER    TBD
// #define encDT  16  // DT ENCODER     TBD
// #define encBTN 39  // encoder button TBD

// LED defines
// TBD

// battery is charging indicator
// TBD

// reading the battery voltage through 33k / 100k voltage divider
// TBD
