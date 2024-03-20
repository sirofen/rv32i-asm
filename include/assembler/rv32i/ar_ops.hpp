#pragma once

// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/ctx.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>

namespace assembler::rv32i::r_type {
class ar_ops : public instruction_base {
public:
    using rv32i_asm_struct = rv32i_context::r_type_rv32i_asm_struct_le;

    ar_ops() = default;
    virtual ~ar_ops() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode(tokenizer tokens,
                        rv32i_asm_struct& asm_struct) const = 0;
};

struct add : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b000;
        asm_struct.funct7 = 0b0000000;
    }
};
struct sub : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b000;
        asm_struct.funct7 = 0b0100000;
    }
};
struct sll : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b001;
        asm_struct.funct7 = 0b0000000;
    }
};
struct slt : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b010;
        asm_struct.funct7 = 0b0000000;
    }
};
struct sltu : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b011;
        asm_struct.funct7 = 0b0000000;
    }
};
struct _xor : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b100;
        asm_struct.funct7 = 0b0000000;
    };
};
struct srl : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b101;
        asm_struct.funct7 = 0b0000000;
    }
};
struct sra : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b101;
        asm_struct.funct7 = 0b0100000;
    }
};
struct _or : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b110;
        asm_struct.funct7 = 0b0000000;
    }
};
struct _and : public ar_ops {
    void encode(tokenizer tokens, rv32i_asm_struct& asm_struct) const override {
        asm_struct.opcode = 0b0110011;
        asm_struct.funct3 = 0b111;
        asm_struct.funct7 = 0b0000000;
    }
};
}  // namespace assembler::rv32i::r_type