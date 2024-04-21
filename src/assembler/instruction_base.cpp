// assembler
#include <assembler/cpu_ctx.hpp>
#include <assembler/instruction_base.hpp>

// C++ STL
#include <stdexcept>

namespace assembler {
instruction_base::instruction_base() = default;

void instruction_base::set_ctx(std::shared_ptr<cpu_ctx> ctx) {
    m_ctx = std::move(ctx);
}

std::shared_ptr<cpu_ctx> instruction_base::ctx() const {
    if (!m_ctx) {
        throw std::runtime_error("Context is not initialised");
    }
    return m_ctx;
}

}  // namespace assembler
