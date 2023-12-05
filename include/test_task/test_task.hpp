#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace test_task
{

std::string rm_all_substr(std::string str, const std::string_view substr);

std::vector<std::string> split(const std::string_view str,
                               const std::string_view delimiter);

bool case_insensitive_less(const std::string& lhs, const std::string& rhs);

} // namespace test_task
