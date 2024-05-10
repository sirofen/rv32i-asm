// assembler
#include <assembler/rv32i/store_inst.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::s_type {
boost::asio::mutable_buffer store_inst::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    boost::asio::buffer_cast<rv32i_asm_struct*>(rcv_buf);

    asm_inst_struct->rs2 = utils::register_parse(*++tokens);

    auto imm = ::assembler::utils::parse_str<std::int32_t>(*++tokens);
    asm_inst_struct->imm0_4 = imm & 0x1f;
    asm_inst_struct->imm5_11 = ((imm >> 5) & 0x7F) | ((imm >> 9) & 0b1000000);

    asm_inst_struct->rs1 = utils::register_parse(*++tokens);

    asm_inst_struct->opcode = 0b0100011;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::s_type