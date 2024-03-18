#pragma once

// assembler
#include <assembler/instruction_base.hpp>
#include <assembler/rv32i/ctx.hpp>

// C++ STL
#include <boost/asio/buffer.hpp>

namespace assembler::rv32i::i_type {
class imm_ops : public instruction_base {
public:
    using i_type_struct = rv32i_context::i_type_struct_le;

    imm_ops() = default;
    virtual ~imm_ops() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;

    virtual void encode(tokenizer tokens, i_type_struct& asm_struct) const = 0;
};

struct addi : public imm_ops {
    void encode(tokenizer tokens, i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b000;
    }
};
struct slti : public imm_ops {
    void encode(tokenizer tokens, i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b010;
    }
};
struct sltiu : public imm_ops {
    void encode(tokenizer tokens, i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b011;
    }
};
struct xori : public imm_ops {
    void encode(tokenizer tokens, i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b100;
    }
};
struct ori : public imm_ops {
    void encode(tokenizer tokens, i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b110;
    }
};
struct andi : public imm_ops {
    void encode(tokenizer tokens, i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b0010011;
        asm_struct.funct3 = 0b111;
    }
};

}  // namespace assembler::rv32i::i_type