// GTest
#include <gtest/gtest.h>

// rv32i assembler
#include <assembler/rv32i/i-type/i-type_base.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/token_functions.hpp>

#define GEN_TEST_RV32I_ASM(TEST_NAME, ASM, MACHINE_CODE)         \
    TEST(RV32IAssembler, TEST_NAME) {                            \
        std::uint32_t _b{};                                      \
        ASSERT_NO_THROW(assembler::rv32i::i_type::addi().encode( \
            word_tokenizer(#ASM), {&_b, sizeof(_b)}));           \
        ASSERT_EQ(_b, MACHINE_CODE);                             \
    }

namespace {
constexpr const std::string_view word_separators = " \t\n\r,";
boost::tokenizer<boost::char_separator<char>> word_tokenizer(
    std::string_view input) {
    return {input, boost::char_separator<char>(word_separators.data())};
}
}  // namespace

GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, 3", 0x308f93)

//GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, 3", 0x308f93)

//GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, 3", 0x308f93)

//GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, 3", 0x308f93)

//GEN_TEST_RV32I_ASM(ADDI, "addi t6, ra, 3", 0x308f93)
