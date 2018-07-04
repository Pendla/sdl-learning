cmake_minimum_required(VERSION 2.6)
project(SDLLearning)
add_executable(
    SDLLearning
    src/main.cpp
)
target_link_libraries(
    SDLLearning
    "-framework SDL2"
    "-framework SDL2_image"
)
