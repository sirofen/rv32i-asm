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

GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, -1", 0xfff08f93)
GEN_TEST_RV32I_ASM(SLTI, "slti sp, sp, 3", 0x312113)
GEN_TEST_RV32I_ASM(SLTIU, "sltiu a0, a0, 3", 0x353513)
GEN_TEST_RV32I_ASM(XORI, "xori a1, a1, 3", 0x35C593)
GEN_TEST_RV32I_ASM(ORI, "ori a2, a2, 3", 0x366613)
GEN_TEST_RV32I_ASM(ANDI, "andi a3, a3, 3", 0x36F693)

GEN_TEST_RV32I_ASM(JALR, "jalr sp, -1(sp)", 0xfff10167)

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

GEN_TEST_RV32I_ASM(JAL, "jal ra, -111111", 0xdf9e40ef)

GEN_TEST_RV32I_ASM(BEQ, "beq s7, s7, 0x3", 0x17b8163)
GEN_TEST_RV32I_ASM(BNE, "bne x3, x4, -20", 0xfe4196e3)
GEN_TEST_RV32I_ASM(BLT, "blt x5, x6, 24", 0x62cc63)
GEN_TEST_RV32I_ASM(BGE, "bge x7, x8, -28", 0xfe83d2e3)
GEN_TEST_RV32I_ASM(BLTU, "bltu x9, x10, 32", 0x2a4e063)
GEN_TEST_RV32I_ASM(BGEU, "bgeu x11, x12, -36", 0xfcc5fee3)

GEN_TEST_RV32I_ASM(SB, "sb s4, 0(s4)", 0x14a0023)
GEN_TEST_RV32I_ASM(SH, "sh s5, 2(s5)", 0x15a9123)
GEN_TEST_RV32I_ASM(SW, "sw s6, 3(s6)", 0x16b21a3)

GEN_TEST_RV32I_ASM(LUI, "lui t5, -20", 0xfffecf37)
GEN_TEST_RV32I_ASM(AUIPC, "auipc t6, -0x1", 0xffffff97)