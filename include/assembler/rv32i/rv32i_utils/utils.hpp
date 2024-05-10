#pragma once

// C++ STL
#include <cstdint>
#include <string_view>

// assembler
#include <assembler/instruction_base.hpp>

namespace assembler::rv32i::utils {
std::uint32_t register_parse(std::string_view register_abi_name);

// utility class for initializing data
class string_data : public instruction_base {
public:

    string_data() = default;
    virtual ~string_data() = default;

    boost::asio::mutable_buffer encode(
        tokenizer tokens,
        boost::asio::mutable_buffer rcv_buf) const override final;
};

}