# CMake functions enclose scope: vars created/set here are not visible to the caller
# Call this function to update (and initialise) git submodules
function(update_git_submodules)
    find_package(Git QUIET)     # Find Git
    if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git") # Ensure .git exists
        message(STATUS "Updating git submodules...")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            RESULT_VARIABLE UPDATE_SUBMODULES_RESULT
        )
        if(NOT UPDATE_SUBMODULES_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update failed!")
        endif()
    endif()
endfunction()

# CMake Macros DON'T enclose scope; vars created/set here are in the same scope as the caller
# Call this macro to set platform-specific dependencies in SFML_DEPS
macro(pre_sfml)
    set(SFML_EXTLIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML/extlibs")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # Windows clang builds can't find freetype.h because SFML doesn't configure these paths
        list(APPEND CMAKE_LIBRARY_PATH "${SFML_EXTLIBS_PATH}/libs-msvc-universal/x64")
        list(APPEND CMAKE_LIBRARY_PATH "${SFML_EXTLIBS_PATH}/libs-msvc-universal/x86")
    endif()
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(SFML_DEPS
            freetype
            gdi32
            winmm
            opengl32
        )
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            # MinGW ext libs here located here
            list(APPEND LIB_PATHS "${SFML_EXTLIBS_PATH}/libs-mingw/x64")
            list(APPEND LIB_PATHS "${SFML_EXTLIBS_PATH}/libs-mingw/x86")
        else()
            # MSVC ext libs are located here
            list(APPEND LIB_PATHS "${SFML_EXTLIBS_PATH}/libs-msvc-universal/x64")
            list(APPEND LIB_PATHS "${SFML_EXTLIBS_PATH}/libs-msvc-universal/x86")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(SFML_DEPS
            m
            pthread
            freetype
            GL
            udev
            X11
            Xrandr
        )
    else()
        message(WARNING "Unsupported platform [${CMAKE_SYSTEM_NAME}]!") # Warn users that builds will fail
    endif()
    # Usually this is not required, CMake picks up the binary path when you call `target_link_libraries()`;
    # but for some reason with SFML it doesn't, so we explicitly add its output path as a library search path for snake.
    list(APPEND LIB_PATHS "${CMAKE_CURRENT_BINARY_DIR}/extern/SFML/lib")
    # Same thing here: usually libraries export the include directory so linked targets will auto-include them, but
    # SFML doesn't, so we explicitly include this directory for snake.
    list(APPEND INCLUDE_PATHS extern/SFML/include)
endmacro()
