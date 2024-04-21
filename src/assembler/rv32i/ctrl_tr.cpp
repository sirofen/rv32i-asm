// assembler
#include <assembler/rv32i/ctrl_tr.hpp>
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/utils/utils.hpp>

namespace assembler::rv32i::j_type {
boost::asio::mutable_buffer ctrl_tr::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = rv32i_context::from_buf<rv32i_asm_struct>(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);


    auto imm_val_input = *++token_it;
    std::int32_t imm;
    auto imm_opt = ::assembler::utils::parse_str_no_throw<std::int32_t>(imm_val_input);
    if (imm_opt) {
        imm = *imm_opt;
    } else {
        auto it = ctx()->label.find(std::string(imm_val_input));
        if (it == ctx()->label.cend()) {
            throw std::runtime_error(
                fmt::format("Label '{}' no found", imm_val_input));
        }
        imm = it->second;
    }

    asm_inst_struct->imm12_19 = imm >> 12;
    asm_inst_struct->imm11 = (imm >> 11) & 0b1;
    asm_inst_struct->imm1_10 = imm >> 1;
    asm_inst_struct->imm20 = (imm >> 20) & 0b1;

    encode(tokens, *asm_inst_struct);
    return rcv_buf += (sizeof(rv32i_asm_struct));
}
}  // namespace assembler::rv32i::j_type