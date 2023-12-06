#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace test_task
{

std::string rm_all_substr(std::string str, const std::string_view substr);

std::vector<std::string> split(const std::string_view str,
                               const std::string_view delimiter);

bool case_insensitive_less(const std::string& lhs, const std::string& rhs);

std::optional<std::string> read_file(const std::filesystem::path& filename);

struct input_data
{
    std::filesystem::path input_file;
    std::filesystem::path output_file;
    std::string word_for_deleting;
};

/**
 * @param argc
 * @param argv first arg is word for deleting,
 *             second is input file,
 *             third is output file
 * @return std::optional<input_data>
 */
std::optional<input_data> parse_args(int argc, char** argv);

} // namespace test_task
