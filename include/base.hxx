#pragma once
#include <cstdint>
#include <stdexcept>
#include <format>
using byte = uint8_t;
using word = uint16_t;

inline bool GetByteSignBit(const byte &value){
    return value & 128;
}