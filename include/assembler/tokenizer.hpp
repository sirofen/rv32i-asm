#pragma once

// boost
#include <boost/asio/buffer.hpp>
#include <boost/tokenizer.hpp>

// C++ STL
#include <string>

namespace assembler {
class tokenizer {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = const std::string*;
    using reference = std::string;

    tokenizer(const std::string& input, std::size_t start = 0);

    reference type_info() const;

    reference operator*() const;

    tokenizer& operator++();


    bool operator==(const tokenizer& other) const;
    bool operator!=(const tokenizer& other) const;

private:
    void find_next();

    enum type { instruction, data_section };

    const std::string& m_input;
    std::size_t m_pos;
    std::size_t m_end;
    type m_delim_type;
};
}  // namespace assembler
