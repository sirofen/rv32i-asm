// assembler
#include <assembler/rv32i/i-type/load_inst.hpp>
#include <assembler/rv32i/utils/utils.hpp>

namespace assembler::rv32i::i_type {

boost::asio::mutable_buffer load_inst::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = i_type_struct::from_buf(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);
    asm_inst_struct->imm = std::stoi(*++token_it);
    asm_inst_struct->rs1 = utils::register_parse(*++token_it);

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(i_type_struct));
}
}  // namespace assembler::rv32i::i_type