cmake_minimum_required(VERSION 3.13)

enable_language(C CXX)

project("chip8-emu")

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})
add_compile_options(-Wall -Wextra -Werror -ggdb -Wno-unused-variable
                    -Wno-unused-parameter)

include_directories(include)

file(GLOB source_files "src/*")

add_executable(chip8-emu ${source_files})

target_link_libraries(chip8-emu ${SDL2_LIBRARIES})
