// assembler
#include <assembler/assembler.hpp>
#include <assembler/rv32i/ctx.hpp>

// spdlog
#include <spdlog/spdlog.h>

// boost
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
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
    namespace fs = boost::filesystem;

    assembler::assembler a(std::make_shared<assembler::rv32i::rv32i_context>());

    auto config = parse_command_line(argc, argv);
    fs::ifstream input_file(fs::path(config.input_path));
    std::string content((std::istreambuf_iterator<char>(input_file)),
                        std::istreambuf_iterator<char>());
    input_file.close();

    char buf[0xfc]{};
    a.assemble(content, boost::asio::mutable_buffer(&buf, sizeof(buf)));

    fs::ofstream output_file(fs::path(config.output_path));

    std::size_t intr_len = sizeof(buf) / sizeof(uint32_t);
    for (std::size_t i = 0; i < intr_len; i++) {
        uint32_t* p = reinterpret_cast<uint32_t*>(buf + i * sizeof(uint32_t));
        output_file << std::hex << *p << std::endl;
    }
    output_file.close();

    SPDLOG_INFO("Done");
    return 0;
}
