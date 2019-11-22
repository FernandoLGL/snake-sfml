# 3.13 is required for `target_link_directories`
cmake_minimum_required(VERSION 3.13)

project(snake LANGUAGES CXX)

# Custom global variables
set(TARGET_NAME snake)
set(INCLUDE_PATHS "")
set(LIB_PATHS "")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Explicitly set the default build configuration (will be blank otherwise)
set(CMAKE_BUILD_TYPE Debug)

# Prevent in-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "FATAL: In-source builds are not allowed.\nYou should create a separate directory for build files.")
endif()

# Force executable outputs for all build configurations to ./bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# CMAKE_CONFIGURATION_TYPES will be empty for single-configuration builds, it only exists for IDE generators like Visual Studio
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${PROJECT_SOURCE_DIR}/bin)
endforeach()

# Output the environment for the user
set(BUILD_CONFIG ${CMAKE_BUILD_TYPE})
if(CMAKE_CONFIGURATION_TYPES)
    set(BUILD_CONFIG "Multi-config")
endif()
message(STATUS "[${CMAKE_SYSTEM_NAME}] [${CMAKE_GENERATOR}] [${CMAKE_CXX_COMPILER_ID}] [${BUILD_CONFIG}]")

# Import utility functions
include(tools/cmake/utils.cmake)

# Ensure all dependencies are present first, otherwise let CMake throw corresponding errors
option(UPDATE_SUBMODULES "Init/Update submodules during generation" ON) # Expose a checkbox in CMake GUI (or an env variable via command line)
if(UPDATE_SUBMODULES)
    update_git_submodules() # Defined in tools/cmake/utils.cmake
endif()

# SFML pre-config
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)     # Don't need network/audio
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)   # Force build static libs
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Add SFML/CMakeLists.txt as a subproject
pre_sfml() # Defined in tools/cmake/utils.cmake
add_subdirectory(extern/SFML)

set(SOURCE
    # add other files here
    src/main.cpp
    src/Snake.cpp
    src/Food.cpp
    src/Game.cpp
)

# Prepend path to current dir to each entry in SOURCE
list(TRANSFORM SOURCE PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
# Source Group makes the source tree in IDEs like Visual Studio match the file tree on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE})

add_executable(${TARGET_NAME} ${SOURCE})
list(APPEND INCLUDE_PATHS include)  # Add ./include to INCLUDE_PATHS

target_include_directories(${TARGET_NAME} SYSTEM PUBLIC ${INCLUDE_PATHS})   # Set up include paths
target_compile_definitions(${TARGET_NAME} PUBLIC SFML_STATIC)       # Pre-processor macros
target_link_directories(${TARGET_NAME} PUBLIC ${LIB_PATHS})     # Linker paths
# Link these libraries to this project; SFML builds debug outputs with a `-d` suffix (and static outputs with `-s`), hence the generator expression
target_link_libraries(${TARGET_NAME} PUBLIC
    sfml-graphics-s$<$<CONFIG:Debug>:-d>
    sfml-window-s$<$<CONFIG:Debug>:-d>
    sfml-system-s$<$<CONFIG:Debug>:-d>
    ${SFML_DEPS}    # Set by set_sfml_deps()
)

# Adding dependencies makes the listed targets build before TARGET_NAME
add_dependencies(${TARGET_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)
