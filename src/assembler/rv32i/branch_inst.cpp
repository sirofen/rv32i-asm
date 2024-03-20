// assembler
#include <assembler/rv32i/branch_inst.hpp>
#include <assembler/rv32i/utils/utils.hpp>
#include <assembler/instruction_base.hpp>

// boost
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::b_type {
boost::asio::mutable_buffer branch_inst::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rs1 = utils::register_parse(*++token_it);
    asm_inst_struct->rs2 = utils::register_parse(*++token_it);

    auto imm = ::assembler::utils::parse_str<std::int16_t>(*++token_it);
    asm_inst_struct->imm11 = (imm >> 11) & 0b1;
    asm_inst_struct->imm1_4 = (imm >> 1) & 0xF;
    asm_inst_struct->imm5_10 = (imm >> 5) & 0x3F;
    asm_inst_struct->imm12 = (imm >> 15) & 0b1;

    asm_inst_struct->opcode = 0b1100011;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::b_type