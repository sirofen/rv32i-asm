#pragma once

// boost
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>

namespace assembler {
class instruction_base {
public:
    template <typename S>
    boost::asio::mutable_buffer advance_buf(boost::asio::mutable_buffer b) const {
        return {reinterpret_cast<void*>(
                    reinterpret_cast<std::ptrdiff_t>(b.data()) + sizeof(S)),
                b.size() - sizeof(S)};
    }
    using tokenizer = boost::tokenizer<boost::char_separator<char>>;

    instruction_base();
    virtual ~instruction_base() = default;

    virtual boost::asio::mutable_buffer encode(
        tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const = 0;
};
}  // namespace assembler
