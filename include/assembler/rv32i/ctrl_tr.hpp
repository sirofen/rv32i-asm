#pragma once

// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/ctx.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>

namespace assembler::rv32i::j_type {
class ctrl_tr : public instruction_base {
public:
    using rv32i_asm_struct = rv32i_context::j_type_rv32i_asm_struct_le;

    ctrl_tr() = default;
    virtual ~ctrl_tr() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode(tokenizer tokens,
                        rv32i_asm_struct& asm_struct) const = 0;
};

struct jal : public ctrl_tr {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b1101111;
    }
};
}  // namespace assembler::rv32i::j_type