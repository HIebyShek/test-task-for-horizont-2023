#include <test_task/test_task.hpp>

#include <algorithm>

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
split(const std::string_view str, const std::string_view delimiter)
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

} // namespace test_task