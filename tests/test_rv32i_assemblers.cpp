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

GEN_TEST_RV32I_ASM(ADD, "add ra, sp, gp", 0x3100B3)
GEN_TEST_RV32I_ASM(SUB, "sub tp, t0, t1", 0x40628233)
GEN_TEST_RV32I_ASM(SLL, "sll t2, s0, fp", 0x8413B3)
GEN_TEST_RV32I_ASM(SLT, "slt s1, a0, a1", 0xB524B3)
GEN_TEST_RV32I_ASM(SLTU, "sltu a2, a3, a4", 0xE6B633)
GEN_TEST_RV32I_ASM(XOR, "xor a5, a6, a7", 0x11847B3)
GEN_TEST_RV32I_ASM(SRL, "srl s2, s3, s4", 0x149D933)
GEN_TEST_RV32I_ASM(SRA, "sra s5, s6, s7", 0x417B5AB3)
GEN_TEST_RV32I_ASM(OR, "or s8, s9, s10", 0x1ACEC33)
GEN_TEST_RV32I_ASM(AND, "and t3, t4, t5", 0x1EEFE33)

GEN_TEST_RV32I_ASM(JAL, "jal ra, 0", 0xef)