// assembler
#include <assembler/instructions_fabric.hpp>
// rv32i
#include <assembler/rv32i/ctx.hpp>
#include <assembler/rv32i/i-type/load_inst.hpp>
#include <assembler/rv32i/i-type/imm_ops.hpp>
#include <assembler/rv32i/i-type/ctrl_tr.hpp>

// C++ STL
#include <memory>
#include <stdexcept>

// fmt
#include <fmt/format.h>

namespace assembler {
instructions_fabric& instructions_fabric::instance() {
    static instructions_fabric i;
    return i;
}

instructions_fabric::instructions_fabric()
    : m_instruction_names()
    , m_instruction_handlers() {
    auto shared_ctx = std::make_shared<rv32i::rv32i_context>();

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


    for (auto& [_, handler] : m_instruction_handlers) {
        handler->set_ctx(shared_ctx);
    }
}

const std::unordered_set<std::string_view>&
instructions_fabric::instruction_names() const {
    return m_instruction_names;
}

const assembler::instruction_base& instructions_fabric::get_handler_for(
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