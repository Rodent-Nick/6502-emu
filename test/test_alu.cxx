#include "catch2/catch_all.hpp"
#include "alu.hxx"

TEST_CASE("ALU functions nominal", "[alu]"){
    Registers reg{};
    ALU alu{reg};
    SECTION("Test DoAddition with overflow (ADC)"){
        
        byte operand_a = GENERATE(take(128, random(0, 255)));
        byte operand_b = GENERATE(take(128, random(0, 255)));
        bool flag_c = GENERATE(take(2, random(0, 1)));

        reg.sr[FLAG_C] = flag_c;
        alu.ar = operand_a;
        alu.br = operand_b;

        bool sign_a = GetByteSignBit(operand_a);
        bool sign_b = GetByteSignBit(operand_b);
        bool sign_res = byte(operand_a + operand_b + flag_c) & 0x80;

        INFO("operand_a: " << int(operand_a));
        INFO("operand_b: " << int(operand_b));
        INFO("flag_c: " << flag_c);

        /// I am not sure why I wrote this unit test, because the assertion is
        /// using the same method as the tested ALU... so if I really fxxked up,
        /// this unit test wouldn't save me.

        REQUIRE(alu.DoAddition() == byte(operand_a + operand_b + flag_c));
        REQUIRE(reg.sr[FLAG_Z] == (byte(operand_a + operand_b + flag_c) == 0));
        REQUIRE(reg.sr[FLAG_N] == (byte(operand_a + operand_b + flag_c) > 127));
        REQUIRE(reg.sr[FLAG_V] == ((sign_a ^ sign_res) & (sign_b ^ sign_res)));
        REQUIRE(reg.sr[FLAG_C] == (operand_a + operand_b + flag_c) > 255);
    }
}