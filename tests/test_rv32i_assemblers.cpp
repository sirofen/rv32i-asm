// GTest
#include <gtest/gtest.h>

// rv32i assembler
#include <assembler/assembler.hpp>

// boost
#include <boost/asio/buffer.hpp>
#include <boost/token_functions.hpp>

namespace {
static assembler::assembler rv32i_assembler;
}

#define GEN_TEST_RV32I_ASM(TEST_NAME, ASM, MACHINE_CODE)                    \
    TEST(RV32IAssembler, TEST_NAME) {                                       \
        std::uint32_t _b{};                                                 \
        ASSERT_NO_THROW(rv32i_assembler.assemble(#ASM, {&_b, sizeof(_b)})); \
        ASSERT_EQ(_b, MACHINE_CODE);                                        \
    }

GEN_TEST_RV32I_ASM(LW, "lw s1, 3(s1)", 0x34a483)
GEN_TEST_RV32I_ASM(LH, "lh s0, 3(s0)", 0x341403)
GEN_TEST_RV32I_ASM(LHU, "lhu s3, 4(s3)", 0x49d983)
GEN_TEST_RV32I_ASM(LB, "lb a7, 3(a7)", 0x388883)
GEN_TEST_RV32I_ASM(LBU, "lbu s2, 3(s2)", 0x394903)

GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, 3", 0x308F93)
GEN_TEST_RV32I_ASM(SLTI, "slti sp, sp, 3", 0x312113)
GEN_TEST_RV32I_ASM(SLTIU, "sltiu a0, a0, 3", 0x353513)
GEN_TEST_RV32I_ASM(XORI, "xori a1, a1, 3", 0x35C593)
GEN_TEST_RV32I_ASM(ORI, "ori a2, a2, 3", 0x366613)
GEN_TEST_RV32I_ASM(ANDI, "andi a3, a3, 3", 0x36F693)

GEN_TEST_RV32I_ASM(JALR, "jalr sp, 3(sp)", 0x310167)
