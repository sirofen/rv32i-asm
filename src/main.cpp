// assembler
#include <assembler/assembler.hpp>

// spdlog
#include <spdlog/spdlog.h>


int main() {
    assembler::assembler a;

    std::uint32_t buf;
    a.assemble("jal ra, -0x1", boost::asio::mutable_buffer(&buf, sizeof(buf)));

    SPDLOG_INFO("Machine code: {:#x}", buf);
    return 0;
}
