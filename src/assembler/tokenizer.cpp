// assembler
#include <assembler/tokenizer.hpp>

namespace {
constexpr char data_key = '.';
constexpr char skip_chars[] = " \t\n\r,()";
}  // namespace

namespace assembler {
tokenizer::tokenizer(const std::string& input, std::size_t start)
    : m_input(input)
    , m_pos(start)
    , m_end(0)
    , m_delim_type(type::instruction) {
    find_next();

    if (m_input[m_pos] == data_key) {
        m_delim_type = type::data_section;
    }
}

tokenizer::reference tokenizer::operator*() const {
    return m_input.substr(m_pos, m_end - m_pos);
}

tokenizer::reference tokenizer::type_info() const {
    auto begin = m_input.find_first_not_of(skip_chars, 0);

    if (begin == std::string::npos) {
        return "";
    }

    auto end = m_input.find_first_of(skip_chars, begin);
    return m_input.substr(begin, end - begin);
}

tokenizer& tokenizer::operator++() {
    m_pos = (m_end == std::string::npos) ? std::string::npos : m_end + 1;
    find_next();
    return *this;
}

void tokenizer::find_next() {
    m_pos = m_input.find_first_not_of(skip_chars, m_pos);
    if (m_delim_type == type::instruction) {
        m_end = m_input.find_first_of(skip_chars, m_pos);
        return;
    }
    // .string 0x100, "Hello Buddy!"
    if (m_input[m_pos] == '\"') {
        m_end = m_input.find('\"', ++m_pos);
        return;
    }
    m_end = m_input.find_first_of(skip_chars, m_pos);
}
}  // namespace assembler
