#pragma once 
#include <Arduino.h>
static constexpr uint8_t BatteryIconHeight{8};
static constexpr uint8_t BatteryIconWidth{16};

static const unsigned char PROGMEM battery100Percent[] = {
    0b01111111, 0b11111100,
    0b10000000, 0b00000010,
    0b10110110, 0b11011010,
    0b10110110, 0b11011011,
    0b10110110, 0b11011011,
    0b10110110, 0b11011010,
    0b10000000, 0b00000010,
    0b01111111, 0b11111100,
};

static const unsigned char PROGMEM battery75Percent[] = {
    0b01111111, 0b11111100,
    0b10000000, 0b00000010,
    0b10110110, 0b11000010,
    0b10110110, 0b11000011,
    0b10110110, 0b11000011,
    0b10110110, 0b11000010,
    0b10000000, 0b00000010,
    0b01111111, 0b11111100,
};

static const unsigned char PROGMEM battery50Percent[] = {
    0b01111111, 0b11111100,
    0b10000000, 0b00000010,
    0b10110110, 0b00000010,
    0b10110110, 0b00000011,
    0b10110110, 0b00000011,
    0b10110110, 0b00000010,
    0b10000000, 0b00000010,
    0b01111111, 0b11111100,
};

static const unsigned char PROGMEM battery25Percent[] = {
    0b01111111, 0b11111100,
    0b10000000, 0b00000010,
    0b10110000, 0b00000010,
    0b10110000, 0b00000011,
    0b10110000, 0b00000011,
    0b10110000, 0b00000010,
    0b10000000, 0b00000010,
    0b01111111, 0b11111100,
};

static const unsigned char PROGMEM batteryWARNING[] = {
    0b01111111, 0b11111100,
    0b10000000, 0b00000010,
    0b10010000, 0b01100010,
    0b10010000, 0b10010011,
    0b10010000, 0b10010011,
    0b10011100, 0b01100010,
    0b10000000, 0b00000010,
    0b01111111, 0b11111100,
};

const unsigned char *batteryStates[5]{battery100Percent, battery75Percent,
                                      battery50Percent, battery25Percent,
                                      batteryWARNING};

static constexpr uint8_t BatteryChargingIconHeight{8};
static constexpr uint8_t BatteryChargingIconWidth{8};
static const unsigned char PROGMEM batteryCharging[] = {
    0b00000000,
    0b00000010,
    0b00001100,
    0b00111000,
    0b01111110,
    0b00011100,
    0b00110000,
    0b01000000,
};