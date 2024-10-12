/**
 * hardwareDef.hpp
 * brief   : defining the pins for the key matrix
 * created : 21.07.2024
 * creator : @tigmit
 * Licence : opensource
 */
#pragma once
#include <Arduino.h>

// baudrate Speed
static constexpr unsigned long serialBaudRate = 115200;

// Defines for keymatrix:
static constexpr uint8_t row0{34}; // input only pins
static constexpr uint8_t row1{35}; // input only pins
static constexpr uint8_t row2{32};
static constexpr uint8_t row3{33};
static constexpr uint8_t row4{25};

static constexpr uint8_t coll0{26};
static constexpr uint8_t coll1{27};
static constexpr uint8_t coll2{14};
static constexpr uint8_t coll3{12};

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
static constexpr uint8_t numLeds{17};
static constexpr uint8_t LedControllPin{19};

// battery is charging indicator
static constexpr uint8_t batteryChargeSense{5};

// reading the battery voltage through 33k / 100k voltage divider
static constexpr uint8_t batteryVoltage{13};