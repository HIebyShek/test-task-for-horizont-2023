#include <test_task/test_task.hpp>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

int
main(int argc, char** argv)
{
    using namespace test_task;

    auto input = parse_args(argc, argv);
    if (not input.has_value())
    {
        std::cerr << "ERROR: invalid input arguments\n";
        std::cerr << "\tfirst arg is word for deleting," << std::endl;
        std::cerr << "\tsecond arg is path to input file" << std::endl;
        std::cerr << "\tthird arg is path to output file" << std::endl;
        return EXIT_FAILURE;
    }

    auto data = read_file(input->input_file);
    if (not data.has_value())
    {
        std::cerr << "ERROR: failed to open or read input file\n";
        return EXIT_FAILURE;
    }

    std::string filtered_data =
        rm_all_substr(std::move(data.value()), input->word_for_deleting);

    std::vector<std::string> lines = split(std::move(filtered_data), "\n");

    std::sort(lines.begin(), lines.end(), case_insensitive_less);

    std::ofstream out_file(input->output_file, std::ios::out);
    if (not out_file.is_open())
    {
        std::cerr << "ERROR: failed to open output file\n";
        return EXIT_FAILURE;
    }

    for (const auto& line : lines)
    {
        out_file.write(line.data(), line.size());
        out_file << '\n';
    }

    return out_file.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}