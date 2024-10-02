/**
 * model.hpp
 * brief   : this file contains all objects. accassible across files
 * created : 07.09.2024
 * creator : @tigmit Licence : opensource
 */
#pragma once

#include "DisplayHandler.hpp"
#include "EncoderHandler.hpp"
#include "keyBoardHandler.hpp"
// init keyboard handler
KeyboardHandler kbdHandler;

// init DispalyHandler
DisplayHandler dspHandler;

// init EncoderHandler
EncoderHandler encHandler;