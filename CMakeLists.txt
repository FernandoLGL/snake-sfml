cmake_minimum_required(VERSION 3.5)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#can't do in-source builds
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

set(SOURCE
        # add other files here
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Snake.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Food.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
        )

add_executable(snake ${SOURCE})

target_include_directories(snake PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(snake PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)


#Still trying to build libraries that will work properly
#target_link_libraries(snake ${CMAKE_SOURCE_DIR}/libs/libsfml-audio-s.a ${CMAKE_SOURCE_DIR}/libs/libsfml-network-s.a ${CMAKE_SOURCE_DIR}/libs/libsfml-window-s.a ${CMAKE_SOURCE_DIR}/libs/libsfml-graphics-s.a ${CMAKE_SOURCE_DIR}/libs/libsfml-system-s.a GL X11 pthread Xext)

#target_link_libraries(snake ${CMAKE_SOURCE_DIR}/libs/libsfml-window-s.a ${CMAKE_SOURCE_DIR}/libs/libsfml-graphics-s.a GL X11 pthread Xext)
