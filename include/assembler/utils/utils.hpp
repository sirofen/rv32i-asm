#pragma once

// C++ STL
#include <optional>
#include <stdexcept>
#include <string_view>

// fmt
#include <fmt/format.h>

// boost
#include <boost/convert.hpp>
#include <boost/convert/strtol.hpp>
#include <boost/filesystem.hpp>

namespace assembler::utils {
template <typename T>
std::optional<T> parse_str_no_throw(std::string_view input) {
    boost::optional<T> res;
    boost::cnv::strtol converter;

    bool is_neg_hex = input.size() >= 4 && input[0] == '-' && input[1] == '0' &&
                      input[2] == 'x';

    if (!is_neg_hex &&
        (input.size() < 3 || input[0] != '0' || input[1] != 'x')) {
        res = boost::convert<T>(input, converter(boost::cnv::parameter::base =
                                                     boost::cnv::base::dec));
    } else {
        if (is_neg_hex) {
            input.remove_prefix(1);
        }
        res = boost::convert<T>(input, converter(boost::cnv::parameter::base =
                                                     boost::cnv::base::hex));
    }

    if (!res) {
        return std::nullopt;
    }

    return is_neg_hex ? -res.value() : res.value();
}

template <typename T>
T parse_str(std::string_view input) {
    boost::optional<T> res;
    boost::cnv::strtol converter;

    bool is_neg_hex = input.size() >= 4 && input[0] == '-' && input[1] == '0' &&
                      input[2] == 'x';

    if (!is_neg_hex &&
        (input.size() < 3 || input[0] != '0' || input[1] != 'x')) {
        res = boost::convert<T>(input, converter(boost::cnv::parameter::base =
                                                     boost::cnv::base::dec));
    } else {
        if (is_neg_hex) {
            input.remove_prefix(1);
        }
        res = boost::convert<T>(input, converter(boost::cnv::parameter::base =
                                                     boost::cnv::base::hex));
    }

    if (!res) {
        throw std::runtime_error(
            fmt::format("Conversion of value '{}' failed", input));
    }

    return is_neg_hex ? -res.value() : res.value();
}

std::string read_file(const std::string& path);
void write_file_hex(const std::string& path, const char* buf, std::size_t size);
void write_file_bin(const std::string& path, const char* buf, std::size_t size);

}  // namespace assembler::utils
