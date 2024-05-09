// assembler
#include <assembler/utils/utils.hpp>

// spdlog
#include <spdlog/spdlog.h>

// fmt
#include <fmt/format.h>

namespace assembler::utils {

std::string read_file(const std::string& path) {
    namespace fs = boost::filesystem;

    SPDLOG_INFO("Reading file: {}", path);

    fs::path file_path(path);
    if (!fs::exists(file_path) || !fs::is_regular_file(file_path)) {
        throw std::runtime_error(fmt::format(
            "File {} does not exist or is not a regular file.", path));
    }

    fs::ifstream input_file(file_path);
    if (!input_file) {
        throw std::runtime_error(fmt::format("Failed to open file.: {}", path));
    }

    std::string content((std::istreambuf_iterator<char>(input_file)),
                        std::istreambuf_iterator<char>());
    input_file.close();
    return content;
}

void write_file_hex(const std::string& path, const char* buf,
                    std::size_t size) {
    namespace fs = boost::filesystem;

    SPDLOG_INFO("Writing file: {}", path);

    fs::path file_path(path);
    fs::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
    if (!output_file) {
        throw std::runtime_error(
            fmt::format("Failed to open file for writing: {}", path));
    }

    std::size_t intr_len = size / sizeof(uint32_t);
    for (std::size_t i = 0; i < intr_len; i++) {
        uint32_t* p = reinterpret_cast<uint32_t*>(const_cast<char*>(buf) +
                                                  i * sizeof(uint32_t));
        output_file << std::hex << *p << std::endl;
    }
    output_file.close();
}

void write_file_bin(const std::string& path, const char* buf,
                    std::size_t size) {
    namespace fs = boost::filesystem;

    SPDLOG_INFO("Writing file: {}", path);

    fs::path file_path(path);
    fs::ofstream output_file(
        file_path, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!output_file) {
        throw std::runtime_error(
            fmt::format("Failed to open file for writing: {}", path));
    }

    output_file.write(buf, size);
    if (!output_file.good()) {
        throw std::runtime_error(
            fmt::format("Failed to write to file: {}", path));
    }

    output_file.close();
}
}  // namespace assembler::utils