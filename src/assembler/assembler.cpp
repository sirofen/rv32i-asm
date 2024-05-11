// assembler
#include <assembler/assembler.hpp>
#include <assembler/cpu_ctx.hpp>
#include <assembler/instructions_fabric.hpp>

// boost
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/asio/buffer.hpp>

// spdlog
#include <spdlog/spdlog.h>

namespace {
constexpr char kComment = '#';
constexpr char kLabel = ':';

boost::char_separator<char> line_sep("\n;");

constexpr std::size_t pc_step = 4;

std::size_t encode_instruction(
    boost::asio::mutable_buffer& buf,
    const assembler::instructions_fabric& m_instructions_fabric,
    const std::string& instruction) {
    assembler::tokenizer tokens(instruction);
    auto ret_buf = m_instructions_fabric.get_handler_for(tokens.type_info())
                       .encode(std::move(tokens), buf);
    auto len =
        static_cast<char*>(ret_buf.data()) - static_cast<char*>(buf.data());
    buf = ret_buf;
    return len;
}
std::size_t get_len(const assembler::instructions_fabric& m_instructions_fabric,
                    const std::string& instruction) {
    char buf[256];
    boost::asio::mutable_buffer mbuf(buf, sizeof(buf));
    std::size_t len = 0;
    try {
        len = encode_instruction(mbuf, m_instructions_fabric, instruction);
    } catch (const assembler::assembler::label_not_found& e) {
        len = e.instr_len;
    }
    return len;
}

}  // namespace

namespace assembler {
assembler::label_not_found::label_not_found(const std::string& msg,
                                            std::size_t len)
    : std::runtime_error(msg)
    , instr_len(len) {}

assembler::assembler(std::shared_ptr<cpu_ctx> cpu_ctx)
    : m_cpu_ctx(cpu_ctx)
    , m_instructions_fabric(instructions_fabric::instance(m_cpu_ctx)) {
    m_cpu_ctx->m_instructions_fabric = &m_instructions_fabric;
    SPDLOG_DEBUG("Supported instructions:");
    for (const auto& inst : m_instructions_fabric.instruction_names()) {
        SPDLOG_DEBUG("{}", inst);
    }
}

boost::asio::mutable_buffer assembler::assemble(
    std::string_view input, boost::asio::mutable_buffer buf) {
    parse_labels(input);

    boost::tokenizer<boost::char_separator<char>> line_tokens(input, line_sep);
    for (const auto& line : line_tokens) {
        if (line.empty()) continue;

        auto comment_pos = line.find(kComment);
        std::string instruction = (comment_pos != std::string::npos)
                                      ? line.substr(0, comment_pos)
                                      : line;

        if (instruction.empty() ||
            boost::algorithm::trim_copy(instruction).empty()) {
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

        m_cpu_ctx->pc +=
            encode_instruction(buf, m_instructions_fabric, instruction);
    }
    for (const auto& lm : m_cpu_ctx->label) {
        SPDLOG_DEBUG("{}: {}", lm.first, lm.second);
    }
    return buf;
}

void assembler::parse_labels(std::string_view input) {
    boost::tokenizer<boost::char_separator<char>> line_tokens(input, line_sep);

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
                    m_cpu_ctx->pc +=
                        get_len(m_instructions_fabric, instruction);
                }
            }
        } else {
            m_cpu_ctx->pc += get_len(m_instructions_fabric, line_trim);
        }
    }
    m_cpu_ctx->pc = 0;
}

}  // namespace assembler
