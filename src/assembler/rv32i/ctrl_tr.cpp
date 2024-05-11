// assembler
#include <assembler/rv32i/ctrl_tr.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::j_type {
boost::asio::mutable_buffer ctrl_tr::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);

    asm_inst_struct->rd = utils::register_parse(*++tokens);

    auto imm_val_input = *++tokens;
    std::int32_t imm;
    auto imm_opt =
        ::assembler::utils::parse_str_no_throw<std::int32_t>(imm_val_input);
    if (imm_opt) {
        imm = *imm_opt;
    } else {
        auto it = ctx()->label.find(std::string(imm_val_input));
        if (it == ctx()->label.cend()) {
            throw assembler::label_not_found(
                fmt::format("Label '{}' not found", imm_val_input), 4);
        }
        imm = it->second - ctx()->pc;
    }

    asm_inst_struct->imm12_19 = imm >> 12;
    asm_inst_struct->imm11 = (imm >> 11) & 0b1;
    asm_inst_struct->imm1_10 = imm >> 1;
    asm_inst_struct->imm20 = (imm >> 20) & 0b1;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::j_type