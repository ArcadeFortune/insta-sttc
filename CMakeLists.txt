cmake_minimum_required(VERSION 3.10.0)
project(insta-sttc VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_executable(insta-sttc src/main.c
  src/audio.c
  src/main.h
  src/micDataManager.c
  src/micDataProcessor.c
  src/client.c
  src/env.h
  src/keyboardHook.c
  )
  
find_package(libwebsockets CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
target_link_libraries(insta-sttc PRIVATE websockets_shared)
target_link_libraries(insta-sttc PRIVATE portaudio)
target_compile_features(insta-sttc PRIVATE c_std_11)
target_compile_options(insta-sttc PRIVATE /experimental:c11atomics)
