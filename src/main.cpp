// assembler
#include <assembler/assembler.hpp>
#include <assembler/rv32i/ctx.hpp>
#include <assembler/utils/utils.hpp>

// spdlog
#include <spdlog/spdlog.h>

// boost
#include <boost/program_options.hpp>

// C++ STL
#include <iostream>
#include <string>

struct app_params {
    std::string input_path;
    std::string output_path;
};

app_params parse_command_line(int argc, char** argv) {
    namespace po = boost::program_options;
    app_params config;
    po::options_description desc("Options");
    desc.add_options()("help,h", "Print help messages")(
        "input,i", po::value<std::string>(&config.input_path)->required(),
        "Input file path")(
        "output,o", po::value<std::string>(&config.output_path)->required(),
        "Output file path");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << "Basic Command Line Parameter App" << std::endl
                      << desc << std::endl;
            exit(0);
        }

        po::notify(vm);
    } catch (po::error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        exit(1);
    }
    return config;
}

int main(int argc, char** argv) {
    assembler::assembler a(std::make_shared<assembler::rv32i::rv32i_context>());
    auto config = parse_command_line(argc, argv);

    auto content = assembler::utils::read_file(config.input_path);

    char buf[8196]{};
    boost::asio::mutable_buffer mbuf(&buf, sizeof(buf));
    auto ret_buf = a.assemble(content, mbuf);
    std::size_t bytes_used =
        static_cast<char*>(ret_buf.data()) - static_cast<char*>(mbuf.data());

    assembler::utils::write_file_hex(config.output_path, buf, bytes_used);

    SPDLOG_INFO("Done");
    return 0;
}
