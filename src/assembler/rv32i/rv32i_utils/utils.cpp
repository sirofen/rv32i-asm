// rv32i assembler
#include <assembler/rv32i/rv32i_utils/utils.hpp>
#include <assembler/rv32i/store_inst.hpp>

// assembler
#include <assembler/assembler.hpp>
#include <assembler/instructions_fabric.hpp>
#include <assembler/utils/utils.hpp>

// C++ STL
#include <exception>
#include <stdexcept>

// boost
#include <boost/lexical_cast.hpp>

// fmt
#include <fmt/format.h>

namespace {

constexpr const std::string_view regs[] = {
    "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
    "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
    "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

boost::asio::mutable_buffer gen_store_data(
    boost::asio::mutable_buffer rcv_buf, std::uint32_t store_start_addr,
    const char* store_buf, std::uint32_t store_size,
    std::shared_ptr<assembler::cpu_ctx> ctx) {
    // amount of instructions store_size * 2 + 4
    if (rcv_buf.size() < store_size * 2 + 4) {
        throw std::runtime_error("Not enough buffer space");
    }
    const auto& addi = ctx->m_instructions_fabric->get_handler_for("addi");
    const auto& store_byte = ctx->m_instructions_fabric->get_handler_for("sb");

    // store start address to t1 reg
    rcv_buf = addi.encode(assembler::tokenizer(fmt::format("addi t1, zero, {}",
                                                           store_start_addr)),
                          rcv_buf);

    for (std::uint32_t i = 0; i < store_size; i++) {
        rcv_buf = addi.encode(assembler::tokenizer(fmt::format(
                                  "addi t2, zero, {:d}", store_buf[i])),
                              rcv_buf);
        rcv_buf = store_byte.encode(
            assembler::tokenizer(fmt::format("sb t2, {}(t1)", i)), rcv_buf);
    }

    // write null terminator
    rcv_buf = store_byte.encode(
        assembler::tokenizer(fmt::format("sb zero, {}(t1)", store_size)),
        rcv_buf);

    // clean t1, and t2
    rcv_buf = addi.encode(assembler::tokenizer("addi t1, zero, 0"), rcv_buf);
    rcv_buf = addi.encode(assembler::tokenizer("addi t2, zero, 0"), rcv_buf);

    return rcv_buf;
}

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
            throw assembler::register_not_found_exception(
                fmt::format("Invalid register name: {}", register_name));
        }
        return reg_n;
    }
    auto it = regs_abi_asm_map.find(register_name);
    if (it == regs_abi_asm_map.end()) {
        throw assembler::register_not_found_exception(
            fmt::format("Invalid register name: {}", register_name));
    }
    return it->second;
}

boost::asio::mutable_buffer string_data::encode(
    tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const {
    auto start_addr = ::assembler::utils::parse_str<std::uint32_t>(*++tokens);
    const auto& string_data = *++tokens;
    return gen_store_data(rcv_buf, start_addr, string_data.data(),
                          string_data.size(), ctx());
}

}  // namespace assembler::rv32i::utils