// assembler
#include <assembler/rv32i/imm_ops.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/instruction_base.hpp>
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::i_type {

boost::asio::mutable_buffer imm_ops::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    boost::asio::buffer_cast<rv32i_asm_struct*>(rcv_buf);

    asm_inst_struct->rd = utils::register_parse(*++tokens);
    asm_inst_struct->rs1 = utils::register_parse(*++tokens);

    auto imm = ::assembler::utils::parse_str<std::int16_t>(*++tokens);
    asm_inst_struct->imm0_11 = imm | ((imm >> 4) & (1 << 11)) ;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::i_type