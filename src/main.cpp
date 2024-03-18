// assembler
#include <assembler/assembler.hpp>

// boost
#include <boost/asio/buffer.hpp>

// tmp
#include <spdlog/spdlog.h>
#include <iostream>
void print_buffer_bits(const char data[], std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        char byte = data[i];
        for (int j = 7; j >= 0; --j) {
            std::cout << ((byte >> j) & 1);
        }
        std::cout << ' ';
    }
    std::cout << std::endl;
}


int main() {
    assembler::assembler a;

    char buf[0xff] {};

    std::string_view input = {"lh s0, 3(s0)"};

    a.assemble("lh s0, 3(s0)", boost::asio::mutable_buffer(buf, sizeof(buf)));

    print_buffer_bits(buf, 4);
    std::uint32_t t = 0x341403;
    print_buffer_bits((char*)&t, 4);
    SPDLOG_INFO("{:x}", *(std::uint32_t*)(&buf));


    return 0;
}
