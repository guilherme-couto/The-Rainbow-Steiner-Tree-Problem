cmake_minimum_required(VERSION 3.10)

project(The-Rainbow-Steiner-Tree-Problem)
file(GLOB source_files
            "*.h"
            "*.hpp"
            "*.cpp"
            "source/*.cpp"
            "include/*.h"
            "include/*.hpp"
    )
add_executable(rstp ${source_files})

include_directories(./include)