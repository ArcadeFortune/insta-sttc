cmake_minimum_required(VERSION 3.10.0)
project(insta-sttc VERSION 0.1.0 LANGUAGES C)

add_subdirectory(external/portaudio)
add_executable(insta-sttc src/main.c)

target_link_libraries(insta-sttc PRIVATE portaudio)
