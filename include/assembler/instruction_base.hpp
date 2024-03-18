#pragma once

// boost
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>

namespace assembler {
class instruction_base {
public:
    using tokenizer = boost::tokenizer<boost::char_separator<char>>;

    instruction_base();
    virtual ~instruction_base() = default;

    virtual boost::asio::mutable_buffer encode(
        tokenizer tokens, boost::asio::mutable_buffer rcv_buf) const = 0;

    void set_ctx(std::shared_ptr<void> ctx);

    template <class T>
    std::shared_ptr<T> ctx() {
        return m_ctx;
    }

private:
    std::shared_ptr<void> m_ctx;
};
}  // namespace assembler
