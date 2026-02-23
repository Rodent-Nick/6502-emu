#include "catch2/catch_all.hpp"
#include "mem.hxx"

TEST_CASE("Memory function is intact", "[mem]") {
    
    Memory mem{};

    SECTION("Memory I/O") {
        // Set upper bound to 0xfffe to prevent word out-of-bound
        word addr = GENERATE(take(256, random(0x0000, 0xfffe)));
        byte data_byte = GENERATE(take(1, random(0x00,0xff)));
        word data_word = GENERATE(take(1, random(0x0000,0xffff)));

        REQUIRE(mem.PeekByte(addr) == 0);
        mem.PutByte(addr, data_byte);
        REQUIRE(mem.PeekByte(addr) == data_byte);
        mem.PutWord(addr, data_word);
        REQUIRE(mem.PeekWord(addr) == data_word);
    }

}
