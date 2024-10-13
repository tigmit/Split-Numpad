/**
 * layout.hpp
 * brief   : defining the layout for the keymatrix
 * created : 21.07.2024
 * creator : @tigmit
 * Licence : opensource
 */
#pragma once
#include "hardwareDef.hpp"
#include <BleKeyboard.h>

uint8_t rows[numRows]{row0, row1, row2, row3, row4};
uint8_t colls[numCols]{coll0, coll1, coll2, coll3};

constexpr uint8_t NC = 0;
constexpr uint8_t KEY_FN_1 = 1;
constexpr uint8_t KEY_FN_2 = 2;

uint8_t layout1[numLayers][numRows][numCols]{
    {
        {KEY_DELETE,               '/',             '*',              '-'},
        {       '7',               '8',             '9',               NC},
        {       '4',               '5',             '6',              '+'},
        {       '1',               '2',             '3',               NC},
        {       '0',                NC,             '.',       KEY_RETURN}
    }
};

bool pressed[numLayers][numRows][numCols] = {OFF};

constexpr uint8_t rgbNC{80}; // out of array
uint8_t rgbLayout[numRows][numCols]{
    {0,      1,  2,     3},
    {4,      5,  6, rgbNC},
    {7,      8,  9,    10},
    {11,    12, 13, rgbNC},
    {14, rgbNC, 15,    16}
};

/*
NOTE: to add more layers. use this template and increase the layercount
the pad is using a 5X4 keymatrix. 
All keys labled as NC are "not connected" and thus not a part of the matrix.

uint8_t yourLayout[numLayers][numRows][numCols]{
    {
        {     ' ',               ' ',             ' ',              ' '},
        {     ' ',               ' ',             ' ',               NC},
        {     ' ',               ' ',             ' ',              ' '},
        {     ' ',               ' ',             ' ',               NC},
        {     ' ',                NC,             ' ',              ' '}
    }
};

*/