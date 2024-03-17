// rv32i assembler
#include <assembler/rv32i/i-type/i-type_base.hpp>
#include <assembler/rv32i/utils/utils.hpp>

// boost
#include <boost/asio/buffer.hpp>
#include <boost/token_functions.hpp>

// C++ STL
#include <memory>

#define ADD_HANDLER(name) \
    { #name, name }

namespace {
boost::asio::mutable_buffer addi(
    boost::tokenizer<boost::char_separator<char>> tokens,
    boost::asio::mutable_buffer rcv_buf) {
    return rcv_buf;
}

std::unordered_map<std::string,
                   std::function<boost::asio::mutable_buffer(
                       boost::tokenizer<boost::char_separator<char>>,
                       boost::asio::mutable_buffer)>>
    instruction_handlers{ADD_HANDLER(addi)};
}  // namespace

namespace assembler::rv32i::i_type {
boost::asio::mutable_buffer i_type_base::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto* asm_inst_struct = i_type_struct::from_buf(rcv_buf);
    auto token_it = tokens.begin();
    asm_inst_struct->rd = utils::register_parse(*++token_it);
    asm_inst_struct->rs1 = utils::register_parse(*++token_it);
    asm_inst_struct->imm = std::stoi(*++token_it);

    encode_i_type(tokens, *asm_inst_struct);
    return advance_buf<i_type_struct>(rcv_buf);
}
}  // namespace assembler::rv32i::i_type
