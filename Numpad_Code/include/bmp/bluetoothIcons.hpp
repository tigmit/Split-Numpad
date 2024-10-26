#pragma once
#include <Arduino.h>

static constexpr uint8_t bleConnectIconHeight{8};
static constexpr uint8_t bleConnectIconWidth{16};

static const unsigned char PROGMEM bleConnected[] = {
    0b00000000, 0b00110000,
    0b00000000, 0b01100000,
    0b00000000, 0b11000000,
    0b00000001, 0b10000000,
    0b11000011, 0b00000000,
    0b01100110, 0b00000000,
    0b00111100, 0b00000000,
    0b00011000, 0b00000000,
};

static const unsigned char PROGMEM bleNotConnected[] = {
    0b00001100, 0b00110000,
    0b00000110, 0b01100000,
    0b00000011, 0b11000000,
    0b00000001, 0b10000000,
    0b00000001, 0b10000000,
    0b00000011, 0b11000000,
    0b00000110, 0b01100000,
    0b00001100, 0b00110000,
};

const unsigned char* bleConnectIcons[2]{bleNotConnected, bleConnected};