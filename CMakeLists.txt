cmake_minimum_required(VERSION 3.10.0)
project(insta-sttc VERSION 0.1.0 LANGUAGES C)

# Enforce C11 for the project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(/experimental:c11atomics)

add_subdirectory(external/portaudio external/libwebsockets)
add_executable(insta-sttc src/main.c
  src/audio.c
  src/main.h
  src/micDataManager.c
  src/micDataProcessor.c)

target_link_libraries(insta-sttc PRIVATE portaudio)

if(WIN32 AND TARGET portaudio)
  add_custom_command(TARGET insta-sttc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:portaudio>
      $<TARGET_FILE_DIR:insta-sttc>
  )
endif()

