// assembler
#include <assembler/rv32i/ar_ops.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>

namespace assembler::rv32i::r_type {

boost::asio::mutable_buffer ar_ops::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);
    asm_inst_struct->rs1 = utils::register_parse(*++token_it);
    asm_inst_struct->rs2 = utils::register_parse(*++token_it);

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::r_type