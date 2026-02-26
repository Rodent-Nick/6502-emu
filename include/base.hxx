#pragma once
#include <cstdint>
#include <stdexcept>
#include <format>
#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>
#include <filesystem>
#include <regex>
using byte = uint8_t;
using word = uint16_t;

#define VERSION_STRING "Alpha (260226A)"

inline bool GetByteSignBit(const byte &value){
    return value & 128;
}