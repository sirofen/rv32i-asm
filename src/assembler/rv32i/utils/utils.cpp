// assembler
#include <assembler/rv32i/utils/utils.hpp>

// C++ STL
#include <exception>
#include <stdexcept>

// boost
#include <boost/lexical_cast.hpp>

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
std::uint32_t register_parse(std::string_view register_name) {
    static auto regs_abi_asm_map = [&]() {
        std::unordered_map<std::string_view, uint32_t> reg_map;
        for (size_t i = 0; i < std::size(regs); ++i) {
            reg_map[regs[i]] = i;
        }
        reg_map["fp"] = 8;
        return reg_map;
    }();
    if (register_name[0] == 'x') {
        auto reg_n =
            boost::lexical_cast<std::uint32_t>(register_name.substr(1));
        if (reg_n > 31) {
            register_not_found_exception(
                fmt::format("Invalid register name: {}", register_name));
        }
        return reg_n;
    }
    auto it = regs_abi_asm_map.find(register_name);
    if (it == regs_abi_asm_map.end()) {
        throw register_not_found_exception(
            fmt::format("Invalid register name: {}", register_name));
    }
    return it->second;
}
}  // namespace assembler::rv32i::utils