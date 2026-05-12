cmake_minimum_required(VERSION 3.14)
project(LibraryManagement)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─────────────────────────────────────────────────────────────
#  External Libraries (auto-download)
# ─────────────────────────────────────────────────────────────
include(FetchContent)

FetchContent_Declare(
    xlnt
    GIT_REPOSITORY https://github.com/tfussell/xlnt.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(xlnt)

FetchContent_Declare(
    tabulate
    GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(tabulate)

# ─────────────────────────────────────────────────────────────
#  Source files (auto-collect all .cpp)
# ─────────────────────────────────────────────────────────────
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/*.cpp"
)

# ─────────────────────────────────────────────────────────────
#  Executable  ← must come BEFORE target_include_directories
# ─────────────────────────────────────────────────────────────
add_executable(LibraryManagement main.cpp ${SOURCES})

# ─────────────────────────────────────────────────────────────
#  Include paths  ← must come AFTER add_executable
# ─────────────────────────────────────────────────────────────
target_include_directories(LibraryManagement PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/book
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/security
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/validation
)

# ─────────────────────────────────────────────────────────────
#  Link libraries
# ─────────────────────────────────────────────────────────────
target_link_libraries(LibraryManagement PRIVATE xlnt tabulate)

# ─────────────────────────────────────────────────────────────
#  Windows: copy xlnt.dll next to the .exe after build
# ─────────────────────────────────────────────────────────────
if(WIN32)
    add_custom_command(TARGET LibraryManagement POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:xlnt>
            $<TARGET_FILE_DIR:LibraryManagement>
        COMMENT "Copying xlnt.dll to executable directory"
    )
endif()
