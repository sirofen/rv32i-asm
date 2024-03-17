// assembler
#include <assembler/instructions_fabric.hpp>
// rv32i
#include <assembler/rv32i/i-type/i-type_base.hpp>

// C++ STL
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
        add_handler("addi", std::make_shared<rv32i::i_type::addi>());
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