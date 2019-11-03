cmake_minimum_required(VERSION 3.5)

project(project-name LANGUAGES CXX)

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
	)

add_executable(project-name ${SOURCE})

target_include_directories(project-name PRIVATE ${PROJECT_SOURCE_DIR}/include)

#example for adding a static library "lib1.a" and another lib called "lib2"
target_link_libraries(project-name PRIVATE ${PROJECT_SOURCE_DIR}/libs/lib1.a lib2)
