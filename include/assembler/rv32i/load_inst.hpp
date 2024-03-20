#pragma once

// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/ctx.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>

namespace assembler::rv32i::i_type {
class load_inst : public instruction_base {
public:
    using rv32i_asm_struct = rv32i_context::i_type_rv32i_asm_struct_le;

    load_inst() = default;
    virtual ~load_inst() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const = 0;
};

struct lw : public load_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0000011;
        asm_struct.funct3 = 0b010;
    }
};
struct lh : public load_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0000011;
        asm_struct.funct3 = 0b001;
    }
};
struct lhu : public load_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0000011;
        asm_struct.funct3 = 0b101;
    }
};
struct lb : public load_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0000011;
        asm_struct.funct3 = 0b000;
    }
};
struct lbu : public load_inst {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0000011;
        asm_struct.funct3 = 0b100;
    }
};
struct jalr : public load_inst {
    void encode(tokenizer tokens,
                       rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b1100111;
        asm_struct.funct3 = 0b000;
    }
};

}  // namespace assembler::rv32i::i_type