// assembler
#include <assembler/cpu_ctx.hpp>
#include <assembler/instructions_fabric.hpp>
// rv32i
#include <assembler/rv32i/ar_ops.hpp>
#include <assembler/rv32i/branch_inst.hpp>
#include <assembler/rv32i/ctrl_tr.hpp>
#include <assembler/rv32i/ctx.hpp>
#include <assembler/rv32i/imm_ops.hpp>
#include <assembler/rv32i/load_inst.hpp>
#include <assembler/rv32i/store_inst.hpp>
#include <assembler/rv32i/upper_imm_inst.hpp>

// data init
#include <assembler/rv32i/rv32i_utils/utils.hpp>

// C++ STL
#include <memory>
#include <stdexcept>

// fmt
#include <fmt/format.h>

namespace assembler {
instructions_fabric& instructions_fabric::instance(
    std::shared_ptr<cpu_ctx> cpu_ctx) {
    static instructions_fabric i(std::move(cpu_ctx));
    return i;
}

instructions_fabric::instructions_fabric(std::shared_ptr<cpu_ctx> shared_ctx)
    : m_instruction_names()
    , m_instruction_handlers() {
    add_handler("lw", std::make_shared<rv32i::i_type::lw>());
    add_handler("lh", std::make_shared<rv32i::i_type::lh>());
    add_handler("lhu", std::make_shared<rv32i::i_type::lhu>());
    add_handler("lb", std::make_shared<rv32i::i_type::lb>());
    add_handler("lbu", std::make_shared<rv32i::i_type::lbu>());

    add_handler("addi", std::make_shared<rv32i::i_type::addi>());
    add_handler("slti", std::make_shared<rv32i::i_type::slti>());
    add_handler("sltiu", std::make_shared<rv32i::i_type::sltiu>());
    add_handler("xori", std::make_shared<rv32i::i_type::xori>());
    add_handler("ori", std::make_shared<rv32i::i_type::ori>());
    add_handler("andi", std::make_shared<rv32i::i_type::andi>());

    add_handler("jalr", std::make_shared<rv32i::i_type::jalr>());

    add_handler("add", std::make_shared<rv32i::r_type::add>());
    add_handler("sub", std::make_shared<rv32i::r_type::sub>());
    add_handler("sll", std::make_shared<rv32i::r_type::sll>());
    add_handler("slt", std::make_shared<rv32i::r_type::slt>());
    add_handler("sltu", std::make_shared<rv32i::r_type::sltu>());
    add_handler("xor", std::make_shared<rv32i::r_type::_xor>());
    add_handler("srl", std::make_shared<rv32i::r_type::srl>());
    add_handler("sra", std::make_shared<rv32i::r_type::sra>());
    add_handler("or", std::make_shared<rv32i::r_type::_or>());
    add_handler("and", std::make_shared<rv32i::r_type::_and>());

    add_handler("jal", std::make_shared<rv32i::j_type::jal>());

    add_handler("beq", std::make_shared<rv32i::b_type::beq>());
    add_handler("bne", std::make_shared<rv32i::b_type::bne>());
    add_handler("blt", std::make_shared<rv32i::b_type::blt>());
    add_handler("bge", std::make_shared<rv32i::b_type::bge>());
    add_handler("bltu", std::make_shared<rv32i::b_type::bltu>());
    add_handler("bgeu", std::make_shared<rv32i::b_type::bgeu>());

    add_handler("sb", std::make_shared<rv32i::s_type::sb>());
    add_handler("sh", std::make_shared<rv32i::s_type::sh>());
    add_handler("sw", std::make_shared<rv32i::s_type::sw>());

    add_handler("lui", std::make_shared<rv32i::u_type::lui>());
    add_handler("auipc", std::make_shared<rv32i::u_type::auipc>());

    // data init
    add_handler(".string", std::make_shared<rv32i::utils::string_data>());

    for (auto& [_, handler] : m_instruction_handlers) {
        handler->set_ctx(shared_ctx);
    }
}

const std::unordered_set<std::string_view>&
instructions_fabric::instruction_names() const {
    return m_instruction_names;
}

const instruction_base& instructions_fabric::get_handler_for(
    std::string_view instruction_name) const {
    auto iter = m_instruction_handlers.find(instruction_name);
    if (iter == m_instruction_handlers.end()) {
        throw std::invalid_argument(
            fmt::format("Unsupported instruction: '{}'", instruction_name));
    }
    return *iter->second;
}

void instructions_fabric::add_handler(
    std::string_view name,
    std::shared_ptr<instruction_base> instruction_handler) {
    m_instruction_names.insert(name);
    m_instruction_handlers[name] = std::move(instruction_handler);
}

}  // namespace assembler