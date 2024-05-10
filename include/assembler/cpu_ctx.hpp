#pragma once

// C++ STL
#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

// forward declaration
namespace assembler {
class instructions_fabric;
}

namespace assembler {
struct cpu_ctx {
    void add_label(std::string_view label_name);
    void add_label(std::string_view label_name, std::uint64_t label_addr);

    std::uint64_t pc = 0;
    std::unordered_map<std::string, std::uint64_t> label;

    const instructions_fabric* m_instructions_fabric;
};
}  // namespace assembler
