#pragma once

// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/ctx.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>

namespace assembler::rv32i::s_type {
class store_inst : public instruction_base {
public:
    using rv32i_asm_struct = rv32i_context::s_type_rv32i_asm_struct_le;

    store_inst() = default;
    virtual ~store_inst() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode(tokenizer tokens,
                        rv32i_asm_struct& asm_struct) const = 0;
};
struct sb : public store_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b000;
    }
};
struct sh : public store_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b001;
    }
};
struct sw : public store_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b010;
    }
};

}  // namespace assembler::rv32i::s_type