#include <doctest/doctest.h>

#include <iterator>
#include <test_task/test_task.hpp>

#include <algorithm>

#include <iostream>

TEST_CASE("rm_all_substr_from")
{
    SUBCASE("typical")
    {
        std::string tmp = "hello world, world";
        REQUIRE_EQ(test_task::rm_all_substr(tmp, "world"), "hello , ");
        REQUIRE_NE(test_task::rm_all_substr(tmp, "world"), "wrong string");

        REQUIRE_EQ(test_task::rm_all_substr("aaaaaa", "a"), "");
    }

    SUBCASE("empty") { REQUIRE_EQ(test_task::rm_all_substr("", ""), ""); }
}

TEST_CASE("split string by delimiter")
{
    SUBCASE("typical")
    {
        std::vector<std::string> vec{ "123", "456", "789" };
        REQUIRE_EQ(test_task::split("123\n456\n789", "\n"), vec);
    }

    SUBCASE("empty delimiter")
    {
        std::vector<std::string> vec{ "" };
        REQUIRE_EQ(test_task::split("", ""), vec);

        std::vector<std::string> vec2{ "abc" };
        REQUIRE_EQ(test_task::split("abc", ""), vec2);
    }
}

TEST_CASE("sort strings")
{
    std::vector<std::string> vec{ "bca", "abc", "Abc" };
    std::vector<std::string> sorted{ "abc", "Abc", "bca" };

    std::sort(vec.begin(), vec.end(), test_task::case_insensitive_less);
    REQUIRE(vec == sorted);
}
