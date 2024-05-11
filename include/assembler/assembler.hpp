#pragma once
// assembler
#include <assembler/tokenizer.hpp>

// boost
#include <boost/asio/buffer.hpp>
#include <boost/tokenizer.hpp>

// C++ STL
#include <stdexcept>
#include <string_view>

// forward declaration
namespace assembler {
class instructions_fabric;
struct cpu_ctx;
}  // namespace assembler

namespace assembler {
class assembler {
public:
    struct label_not_found : public std::runtime_error {
        label_not_found(const std::string& msg, std::size_t len = 0);
        std::size_t instr_len;
    };
    struct register_not_found_exception : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    assembler(std::shared_ptr<cpu_ctx> cpu_ctx);

    assembler(assembler&& other) = delete;
    assembler& operator=(assembler&& other) = delete;
    assembler(const assembler& other) = delete;
    assembler& operator=(const assembler& other) = delete;

    boost::asio::mutable_buffer assemble(std::string_view input,
                                         boost::asio::mutable_buffer buf);

private:
    void parse_labels(std::string_view input);

    std::shared_ptr<cpu_ctx> m_cpu_ctx;
    const instructions_fabric& m_instructions_fabric;
};
}  // namespace assembler
