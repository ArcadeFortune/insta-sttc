cmake_minimum_required(VERSION 3.10.0)
project(insta-sttc VERSION 0.1.0 LANGUAGES C)

add_executable(insta-sttc src/main.c
  src/audio.c
  src/main.h
  src/micDataManager.c
  src/micDataProcessor.c)
  
find_package(libwebsockets CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
target_link_libraries(insta-sttc PRIVATE websockets_shared)
target_link_libraries(insta-sttc PRIVATE portaudio)

if(WIN32 AND TARGET portaudio)
  add_custom_command(TARGET insta-sttc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:portaudio>
      $<TARGET_FILE_DIR:insta-sttc>
  )
endif()

