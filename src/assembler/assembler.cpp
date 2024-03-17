// assembler
#include <assembler/assembler.hpp>
#include <assembler/instructions_fabric.hpp>

// spdlog
#include <spdlog/spdlog.h>

namespace {
constexpr const std::string_view line_separators = "\n;";
constexpr const std::string_view word_separators = " \t\n\r,";
}  // namespace

namespace assembler {
assembler::assembler()
    : m_instructions_fabric(instructions_fabric::instance()) {
    SPDLOG_INFO("Supported instructions:");
    for (const auto& inst : m_instructions_fabric.instruction_names()) {
        SPDLOG_INFO("{}", inst);
    }
}

void assembler::assemble(std::string_view input,
                         boost::asio::mutable_buffer buf) {
    boost::char_separator<char> line_sep(line_separators.data());
    boost::char_separator<char> word_sep(word_separators.data());
    boost::tokenizer<decltype(line_sep)> line_tokens(input, line_sep);
    for (const auto& line : line_tokens) {
        if (line.empty()) continue;

        boost::tokenizer<decltype(word_sep)> tokens(line, word_sep);
        buf = m_instructions_fabric.get_handler_for(*tokens.begin())
                  .encode(std::move(tokens), buf);
    }
}

}  // namespace assembler
