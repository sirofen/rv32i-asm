// assembler
#include <assembler/rv32i/j-type/ctrl_tr.hpp>
#include <assembler/rv32i/utils/utils.hpp>

namespace assembler::rv32i::j_type {

boost::asio::mutable_buffer ctrl_tr::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_asm_struct::from_buf(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);
    asm_inst_struct->imm12_31 = std::stoi(*++token_it);

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::j_type