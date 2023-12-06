#include <test_task/test_task.hpp>

#include <algorithm>
#include <fstream>

namespace test_task
{

std::string
rm_all_substr(std::string str, const std::string_view substr)
{
    auto len{ substr.size() };
    if (0 == len)
    {
        return str;
    }

    auto pos{ str.find(substr) };
    while (pos != str.npos)
    {
        str.erase(pos, len);
        pos = str.find(substr);
    }
    return str;
}

std::vector<std::string>
split(std::string&& str, const std::string_view delimiter)
{
    std::vector<std::string> ret;

    using size_type = std::string::size_type;
    size_type delimiter_len = delimiter.size();
    size_type delimiter_pos{ str.find_first_of(delimiter) };
    size_type skip{ 0 };
    while (delimiter_pos != str.npos)
    {
        ret.emplace_back(str, skip, delimiter_pos - skip);

        skip = delimiter_pos + delimiter_len;
        delimiter_pos = str.find_first_of(delimiter, skip);
    }
    ret.emplace_back(str, skip, delimiter_pos);

    return ret;
}

namespace details
{

bool
ichar_less(char lhs, char rhs)
{
    return std::tolower(static_cast<unsigned char>(lhs)) <
           std::tolower(static_cast<unsigned char>(rhs));
}

} // namespace details

bool
case_insensitive_less(const std::string& lhs, const std::string& rhs)
{
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), details::ichar_less);
}

std::optional<std::string>
read_file(const std::filesystem::path& filename)
{
    std::ifstream file(filename, std::ios::in);
    if (not file.is_open())
    {
        return std::nullopt;
    }

    std::error_code err;
    std::size_t file_size = std::filesystem::file_size(filename, err);
    if (err.default_error_condition())
    {
        return std::nullopt;
    }

    std::string data(file_size, '\0');
    file.read(data.data(), file_size);

    return data;
}

std::optional<input_data>
parse_args(int argc, char** argv)
{
    if (argc != 1 + 3) // implicit first arg is path to executable
    {
        return std::nullopt;
    }

    input_data input;
    input.word_for_deleting = *(argv + 1);
    input.input_file = *(argv + 2);
    input.output_file = *(argv + 3);

    return input;
}

} // namespace test_task