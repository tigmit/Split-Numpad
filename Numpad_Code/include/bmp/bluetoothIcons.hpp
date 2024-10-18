#pragma once
#include <Arduino.h>

static constexpr uint8_t bleConnectIconHeight{8};
static constexpr uint8_t bleConnectIconWidth{16};

static const unsigned char PROGMEM bleConnected[] = {
    0b00000000, 0b11100000,
    0b00000000, 0b11111000,
    0b00000000, 0b11111110,
    0b00000000, 0b11111111,
    0b00000000, 0b11111111,
    0b00000000, 0b11111110,
    0b00000000, 0b11111000,
    0b00000000, 0b11100000,
};

static const unsigned char PROGMEM bleNotConnected[] = {
    0b00000111, 0b00000000,
    0b00011111, 0b00000000,
    0b01111111, 0b00000000,
    0b11111111, 0b00000000,
    0b11111111, 0b00000000,
    0b01111111, 0b00000000,
    0b00011111, 0b00000000,
    0b00000111, 0b00000000,
};

const unsigned char* bleConnectIcons[2]{bleNotConnected, bleConnected};