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
static constexpr uint8_t row0{26}; // tbd
static constexpr uint8_t row1{25}; // tbd
static constexpr uint8_t row2{33}; // tbd
static constexpr uint8_t row3{32}; // tbd
static constexpr uint8_t row4{35}; // tbd

static constexpr uint8_t coll0{27}; // tbd
static constexpr uint8_t coll1{14}; // tbd
static constexpr uint8_t coll2{12}; // tbd
static constexpr uint8_t coll3{13}; // tbd

// Matrix dimentions
static constexpr uint8_t numRows{5};
static constexpr uint8_t numCols{4};
static constexpr uint8_t numLayers{1};

// Define on and off values
static constexpr bool OFF{0};
static constexpr bool ON{1};

// Display Defines
static constexpr uint8_t SCREEN_WIDTH{128}; // OLED display width, in pixels
static constexpr uint8_t SCREEN_HEIGHT{64}; // OLED display height, in pixels
static constexpr int8_t OLED_RESET{-1};     // Reset pin (-1 if default reset)
static constexpr uint8_t SCREEN_ADDRESS{0x3C}; // datasheet for refference

// pins for rotary Encoder
static constexpr int encCLK{2};  // CLK ENCODER
static constexpr int encDT{4};   // DT ENCODER
static constexpr int encBTN{15}; // encoder button

// LED defines
// TBD

// battery is charging indicator
// TBD

// reading the battery voltage through 33k / 100k voltage divider
// TBD
