cmake_minimum_required(VERSION 3.27)
project(test_task DESCRIPTION "parsers constructor - parse everything" LANGUAGES CXX)

add_library(
  test_task STATIC
  src/test_task.cpp
)
target_compile_features(test_task PUBLIC cxx_std_17)
target_include_directories(test_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



option(BUILD_TESTS "Enable building of tests" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)

add_library(sanitizer INTERFACE)
if(ADDRESS_SANITIZER)
    message(STATUS "Using address sanitizer")
    target_compile_options(sanitizer INTERFACE -fsanitize=address)
    target_link_options(sanitizer INTERFACE -fsanitize=address)
endif()

if(BUILD_TESTS)
    enable_testing()

    add_executable(
      tests
      tests/test_task.test.cpp
      tests/main.test.cpp
    )
    target_compile_features(tests PUBLIC cxx_std_17)
    target_link_libraries(tests PUBLIC doctest)
    target_link_libraries(tests PUBLIC sanitizer)
    target_link_libraries(tests PUBLIC test_task)

    add_test(NAME Tests COMMAND tests)
endif()

