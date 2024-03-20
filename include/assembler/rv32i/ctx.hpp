#pragma once

// C++ STL
#include <boost/asio/buffer.hpp>
#include <cstdint>
#include <stdexcept>

// boost
#include <boost/asio.hpp>

namespace assembler::rv32i {
struct rv32i_context {
    template <class T>
    static T* from_buf(boost::asio::mutable_buffer buf) {
        if (buf.size() < sizeof(i_type_rv32i_asm_struct_le)) {
            throw std::runtime_error("Not enough buffer space");
        }
        return boost::asio::buffer_cast<T*>(buf);
    }

#pragma pack(push, 1)
    struct i_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t imm0_11 : 12;
    };

    struct r_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t rs2 : 5;
        uint32_t funct7 : 7;
    };

    struct j_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t imm12_19 : 8;
        uint32_t imm11 : 1;
        uint32_t imm1_10 : 10;
        uint32_t imm20 : 1;
    };

    struct b_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t imm11 : 1;
        uint32_t imm1_4 : 4;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t rs2 : 5;
        uint32_t imm5_10 : 6;
        uint32_t imm12 : 1;
    };

    struct s_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t imm0_4 : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t rs2 : 5;
        uint32_t imm5_11 : 7;
    };
    struct u_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t imm12_31 : 20;
    };

#pragma pack(pop)
};
}  // namespace assembler::rv32i