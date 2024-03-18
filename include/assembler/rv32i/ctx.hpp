#pragma once

// C++ STL
#include <cstdint>
#include <stdexcept>

// boost
#include <boost/asio.hpp>

namespace assembler::rv32i {
struct rv32i_context {
    struct __attribute__((packed)) i_type_struct_le {
        uint32_t opcode : 7;
        uint32_t rd : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t imm : 12;
        static i_type_struct_le* from_buf(boost::asio::mutable_buffer buf) {
            if (buf.size() < sizeof(i_type_struct_le)) {
                throw std::runtime_error("Not enough buffer space");
            }
            return reinterpret_cast<i_type_struct_le*>(buf.data());
        }
    };
};
}  // namespace assembler::rv32i