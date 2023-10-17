cmake_minimum_required(VERSION 3.27)
project(something DESCRIPTION "parsers constructor - parse everything" LANGUAGES CXX)

add_library(
  something STATIC
  src/something.cpp
)
target_compile_features(something PUBLIC cxx_std_20)
target_include_directories(something PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



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
      tests/something.test.cpp
      tests/main.test.cpp
    )
    target_compile_features(tests PUBLIC cxx_std_20)
    target_link_libraries(tests PUBLIC doctest)
    target_link_libraries(tests PUBLIC sanitizer)
    target_link_libraries(tests PUBLIC something)

    add_test(NAME Tests COMMAND tests)
endif()

