/**
 * model.hpp
 * brief   : this file contains all objects. accassible across files
 * created : 07.09.2024
 * creator : @tigmit Licence : opensource
 */
#pragma once

#include "BatteryHandler.hpp"
#include "DisplayHandler.hpp"
#include "EncoderHandler.hpp"
#include "RgbHandler.hpp"
#include "keyBoardHandler.hpp"

namespace Model {

// declare keyboard handler
KeyboardHandler kbdHandler;

// declare DispalyHandler
DisplayHandler dspHandler;

// declare EncoderHandler
EncoderHandler encHandler;

// declare RgbHandler
RgbHandler rgbHandler;

// declare BatteryHandler
BatteryHandler batteryHandler;

} // namespace Model