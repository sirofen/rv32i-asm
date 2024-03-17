#pragma once

// C++ STL
#include <string_view>

namespace assembler {
class tokenizer {
public:
    tokenizer(std::string_view input, char delim);

    std::size_t size() const;

    std::string_view operator[](std::size_t index) const;

private:
    std::string_view m_input_data;
    char m_delim;
};

}  // namespace assembler