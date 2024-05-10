// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/branch_inst.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/utils/utils.hpp>
#include <stdexcept>

namespace assembler::rv32i::b_type {
boost::asio::mutable_buffer branch_inst::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);

    asm_inst_struct->rs1 = utils::register_parse(*++tokens);
    asm_inst_struct->rs2 = utils::register_parse(*++tokens);

    auto imm_val_input = *++tokens;
    std::int16_t imm;
    auto imm_opt =
        ::assembler::utils::parse_str_no_throw<std::int16_t>(imm_val_input);
    if (imm_opt) {
        imm = *imm_opt;
    } else {
        auto it = ctx()->label.find(std::string(imm_val_input));
        if (it == ctx()->label.cend()) {
            throw std::runtime_error(
                fmt::format("Label '{}' no found", imm_val_input));
        }
        imm = it->second - ctx()->pc;
    }

    asm_inst_struct->imm11 = (imm >> 11) & 0b1;
    asm_inst_struct->imm1_4 = (imm >> 1) & 0xF;
    asm_inst_struct->imm5_10 = (imm >> 5) & 0x3F;
    asm_inst_struct->imm12 = (imm >> 15) & 0b1;

    asm_inst_struct->opcode = 0b1100011;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::b_type