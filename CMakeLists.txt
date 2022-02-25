cmake_minimum_required(VERSION 3.1.0)

project(ETL)

file(GLOB_RECURSE HEADERS include/*.hpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Debug src/Main.cpp)
target_compile_options(Debug PUBLIC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Og -g)
target_include_directories(Debug PRIVATE include)

add_executable(Release src/Main.cpp)
target_compile_options(Release PUBLIC -std=c++20 -Wall -Wextra -Wpedantic -Werror -O3)
target_include_directories(Release PRIVATE include)

add_custom_target(Format COMMAND cd ../ && clang-format -style=file -i src/Main.cpp ${SOURCES} ${HEADERS})
