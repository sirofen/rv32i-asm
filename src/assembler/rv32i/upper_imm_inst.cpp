// assembler
#include <assembler/rv32i/upper_imm_inst.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::u_type {
boost::asio::mutable_buffer upper_imm_inst::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    boost::asio::buffer_cast<rv32i_asm_struct*>(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);

    auto imm = ::assembler::utils::parse_str<std::int32_t>(*++token_it);
    asm_inst_struct->imm12_31 = imm | ((imm >> 11) & ( 1 << 20));

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::u_type