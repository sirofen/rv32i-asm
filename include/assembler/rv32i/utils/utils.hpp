#pragma once

// C++ STL
#include <cstdint>
#include <string_view>

namespace assembler::rv32i::utils {
std::uint32_t register_parse(std::string_view register_abi_name);
}