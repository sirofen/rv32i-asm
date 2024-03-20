// assembler
#include <assembler/rv32i/i-type/imm_ops.hpp>
#include <assembler/rv32i/utils/utils.hpp>
#include <assembler/instruction_base.hpp>

// boost
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::i_type {

boost::asio::mutable_buffer imm_ops::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    boost::asio::buffer_cast<rv32i_asm_struct*>(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);
    asm_inst_struct->rs1 = utils::register_parse(*++token_it);

    auto imm = ::assembler::utils::parse_str<std::int16_t>(*++token_it);
    asm_inst_struct->imm0_11 = imm | ((imm >> 4) & (1 << 11)) ;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::i_type