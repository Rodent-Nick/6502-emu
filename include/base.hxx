#pragma once
#include <cstdint>
using byte = uint8_t;
using word = uint16_t;

inline bool GetByteSignBit(const byte &value){
    return value & 128;
}