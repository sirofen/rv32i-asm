// assembler
#include <assembler/rv32i/utils/utils.hpp>

// C++ STL
#include <exception>
#include <stdexcept>

// fmt
#include <fmt/format.h>

namespace {
struct register_not_found_exception : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

constexpr const std::string_view regs[] = {
    "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
    "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
    "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};
}  // namespace

namespace assembler::rv32i::utils {
std::uint32_t register_parse(std::string_view register_abi_name) {
    static auto regs_abi_asm_map = [&]() {
        std::unordered_map<std::string_view, uint32_t> reg_map;
        for (size_t i = 0; i < std::size(regs); ++i) {
            reg_map[regs[i]] = i;
        }
        return reg_map;
    }();
    auto it = regs_abi_asm_map.find(register_abi_name);
    if (it == regs_abi_asm_map.end()) {
        throw register_not_found_exception(
            fmt::format("Invalid register name: {}", register_abi_name));
    }
    return it->second;
}
}  // namespace assembler::rv32i::utils