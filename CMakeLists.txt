cmake_minimum_required(VERSION 3.27)
project(test_task 
        DESCRIPTION "test task for R&D Center Horizont \
                     compeleted in December 2023" 
        LANGUAGES CXX)

add_library(
  test_task STATIC
  src/test_task.cpp
)
target_compile_features(test_task PUBLIC cxx_std_17)
target_include_directories(test_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(test_task PUBLIC -fno-exceptions)


option(BUILD_TESTS "Enable building of tests" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)

add_library(sanitizer INTERFACE)
if(ADDRESS_SANITIZER AND UNIX)
    message(STATUS "Using address sanitizer")
    target_compile_options(sanitizer INTERFACE -fsanitize=address)
    target_link_options(sanitizer INTERFACE -fsanitize=address)
endif()

add_executable(
  main 
  src/main.cpp
)
target_compile_features(main PUBLIC cxx_std_17)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(main PUBLIC -fno-exceptions)
target_link_libraries(main PUBLIC sanitizer)
target_link_libraries(main PUBLIC test_task)

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
    target_compile_definitions(tests PUBLIC DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS)
    target_compile_options(tests PUBLIC -fno-exceptions)

    add_test(NAME Tests COMMAND tests)
endif()

