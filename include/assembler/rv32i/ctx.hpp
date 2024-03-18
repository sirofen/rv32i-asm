#pragma once

// C++ STL
#include <cstdint>
#include <stdexcept>

// boost
#include <boost/asio.hpp>

// tmp
#include <spdlog/spdlog.h>

namespace assembler::rv32i {
struct rv32i_context {
#pragma pack(push, 1)
    struct i_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t imm20_31 : 12;
        static i_type_rv32i_asm_struct_le* from_buf(
            boost::asio::mutable_buffer buf) {
            if (buf.size() < sizeof(i_type_rv32i_asm_struct_le)) {
                throw std::runtime_error("Not enough buffer space");
            }
            return reinterpret_cast<i_type_rv32i_asm_struct_le*>(buf.data());
        }
    };

    struct r_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t rs2 : 5;
        uint32_t funct7 : 7;
        static r_type_rv32i_asm_struct_le* from_buf(
            boost::asio::mutable_buffer buf) {
            if (buf.size() < sizeof(r_type_rv32i_asm_struct_le)) {
                throw std::runtime_error("Not enough buffer space");
            }
            return reinterpret_cast<r_type_rv32i_asm_struct_le*>(buf.data());
        }
    };

    struct j_type_rv32i_asm_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t imm12_31 : 20;
        static j_type_rv32i_asm_struct_le* from_buf(
            boost::asio::mutable_buffer buf) {
            if (buf.size() < sizeof(j_type_rv32i_asm_struct_le)) {
                throw std::runtime_error("Not enough buffer space");
            }
            return reinterpret_cast<j_type_rv32i_asm_struct_le*>(buf.data());
        }
    };
#pragma pack(pop)
};
}  // namespace assembler::rv32i