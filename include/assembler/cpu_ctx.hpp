#pragma once

// C++ STL
#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace assembler {
struct cpu_ctx {
    void add_label(std::string_view label_name);
    void add_label(std::string_view label_name, std::uint64_t label_addr);

    std::uint64_t pc = 0;
    std::unordered_map<std::string, std::uint64_t> label;
};
}  // namespace assembler
