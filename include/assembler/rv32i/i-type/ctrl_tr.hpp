#pragma once

// assembler
#include <assembler/rv32i/i-type/load_inst.hpp>

namespace assembler::rv32i::i_type {
struct jalr : public load_inst {
    void encode(tokenizer tokens,
                       i_type_struct& asm_struct) const override {
        asm_struct.opcode = 0b1100111;
        asm_struct.funct3 = 0b000;
    }
};
}  // namespace assembler::rv32i::i_type