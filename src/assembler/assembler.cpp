// assembler
#include <assembler/assembler.hpp>
#include <assembler/cpu_ctx.hpp>
#include <assembler/instructions_fabric.hpp>

// boost
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>

// spdlog
#include <spdlog/spdlog.h>

namespace {
constexpr char kComment = '#';
constexpr char kLabel = ':';

boost::char_separator<char> line_sep("\n;");
boost::char_separator<char> label_sep(" \t\n\r");
boost::char_separator<char> word_sep(" \t\n\r,()\"");
}  // namespace

namespace assembler {
assembler::assembler(std::shared_ptr<cpu_ctx> cpu_ctx)
    : m_cpu_ctx(cpu_ctx)
    , m_instructions_fabric(instructions_fabric::instance(m_cpu_ctx)) {
    SPDLOG_DEBUG("Supported instructions:");
    for (const auto& inst : m_instructions_fabric.instruction_names()) {
        SPDLOG_DEBUG("{}", inst);
    }
}

boost::asio::mutable_buffer assembler::assemble(
    std::string_view input, boost::asio::mutable_buffer buf) {
    parse_labels(input);

    tokenizer line_tokens(input, line_sep);
    for (const auto& line : line_tokens) {
        if (line.empty()) continue;

        auto comment_pos = line.find(kComment);
        std::string instruction = (comment_pos != std::string::npos) ? line.substr(0, comment_pos) : line;

        if (instruction.empty() || boost::algorithm::trim_copy(instruction).empty()) {
            continue;
        }

        auto label_pos = instruction.find(kLabel);
        if (label_pos != std::string::npos) {
            if (label_pos + 1 < instruction.size()) {
                instruction = instruction.substr(label_pos + 1);
            } else {
                continue;
            }
        }

        tokenizer tokens(instruction, word_sep);
        auto token_it = tokens.begin();
        if (token_it != tokens.end()) {
            const auto& a = m_instructions_fabric.get_handler_for(*token_it);
            buf = a.encode(tokens, buf);
            m_cpu_ctx->pc += 4;
        }
    }
    for (const auto& lm : m_cpu_ctx->label) {
        SPDLOG_INFO("{}: {}", lm.first, lm.second);
    }
    return buf;
}


void assembler::parse_labels(std::string_view input) {
    tokenizer line_tokens(input, line_sep);

    for (const auto& line : line_tokens) {
        auto line_trim = boost::trim_left_copy(line);
        if (line_trim.empty() || line_trim.front() == kComment) {
            continue;
        }

        auto label_pos = line_trim.find(kLabel);
        if (label_pos != std::string_view::npos) {
            auto label = line_trim.substr(0, label_pos);
            m_cpu_ctx->add_label(label);

            if (label_pos + 1 < line_trim.size()) {
                auto instruction = line_trim.substr(label_pos + 1);
                if (!instruction.empty() && instruction.front() != kComment) {
                    m_cpu_ctx->pc += 4;
                }
            }
        } else {
            m_cpu_ctx->pc += 4;
        }
    }
    m_cpu_ctx->pc = 0;
}

}  // namespace assembler
