#pragma once

// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/ctx.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>

namespace assembler::rv32i::b_type {
class branch_inst : public instruction_base {
public:
    using rv32i_asm_struct = rv32i_context::b_type_rv32i_asm_struct_le;

    branch_inst() = default;
    virtual ~branch_inst() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode(tokenizer tokens,
                        rv32i_asm_struct& asm_struct) const = 0;
};

struct beq : public branch_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b000;
    }
};
struct bne : public branch_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b001;
    }
};
struct blt : public branch_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b100;
    }
};
struct bge : public branch_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b101;
    }
};
struct bltu : public branch_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b110;
    }
};
struct bgeu : public branch_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.funct3 = 0b111;
    }
};

}  // namespace assembler::rv32i::b_type