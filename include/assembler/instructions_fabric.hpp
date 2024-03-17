// C++ STL
#include <functional>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

// boost
#include <boost/tokenizer.hpp>

// assembler
#include <assembler/instruction_base.hpp>

namespace assembler {
class instructions_fabric {
public:
    static instructions_fabric& instance();

    const std::unordered_set<std::string_view>& instruction_names() const;

    const instruction_base& get_handler_for(
        std::string_view instruction_name) const;

private:
    instructions_fabric();

    instructions_fabric(const instructions_fabric&) = default;
    instructions_fabric& operator=(const instructions_fabric&) = default;
    instructions_fabric(instructions_fabric&&) = default;
    instructions_fabric& operator=(instructions_fabric&&) = default;

    void add_handler(std::string_view name, std::shared_ptr<instruction_base>);

    std::unordered_set<std::string_view> m_instruction_names;
    std::unordered_map<std::string_view, std::shared_ptr<instruction_base>>
        m_instruction_handlers;
};
}  // namespace assembler