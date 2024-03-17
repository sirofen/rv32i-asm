#pragma once

// boost
#include <boost/asio/buffer.hpp>

// C++ STL
#include <string_view>

// forward declaration
namespace assembler {
class instructions_fabric;
}

namespace assembler {
class assembler {
public:
    assembler();

    assembler(assembler&& other) = delete;
    assembler& operator=(assembler&& other) = delete;
    assembler(const assembler& other) = delete;
    assembler& operator=(const assembler& other) = delete;

    void assemble(std::string_view input, boost::asio::mutable_buffer buf);

private:
    const instructions_fabric& m_instructions_fabric;
};
}  // namespace assembler
