// assembler
#include <assembler/rv32i/j-type/ctrl_tr.hpp>
#include <assembler/rv32i/utils/utils.hpp>

// boost
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::j_type {
boost::asio::mutable_buffer ctrl_tr::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);

    auto imm = ::assembler::utils::parse_str<std::int32_t>(*++token_it);
    asm_inst_struct->imm12_19 = imm >> 12;
    asm_inst_struct->imm11 = (imm >> 11) & 0b1;
    asm_inst_struct->imm1_10 = imm >> 1;
    asm_inst_struct->imm20 = (imm >> 20) & 0b1;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::j_type