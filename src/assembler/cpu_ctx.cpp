// assembler
#include <assembler/cpu_ctx.hpp>

// C++ STL
#include <fmt/format.h>

namespace {
constexpr const char kError[] = "Error: The label '{}' already exists";
}

namespace assembler {
void cpu_ctx::add_label(std::string_view label_name) {
    if (label.find(std::string(label_name)) != label.cend()) {
        throw std::runtime_error(fmt::format(kError, label_name));
    }
    label[std::string(label_name)] = pc;
}

void cpu_ctx::add_label(std::string_view label_name, std::uint64_t label_addr) {
    if (label.find(std::string(label_name)) != label.cend()) {
        throw std::runtime_error(fmt::format(kError, label_name));
    }
    label[std::string(label_name)] = label_addr;
}
}  // namespace assembler