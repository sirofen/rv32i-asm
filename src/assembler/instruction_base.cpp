// assembler
#include <assembler/instruction_base.hpp>

namespace assembler {
instruction_base::instruction_base() = default;

void instruction_base::set_ctx(std::shared_ptr<void> ctx) {
    m_ctx = std::move(ctx);
}
}  // namespace assembler
