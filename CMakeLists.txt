cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME Logger)
project(
    ${PROJECT_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

set(EXEC_NAME test-logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

file(
    GLOB_RECURSE
    SOURCE_FILES
    "src/*.cpp"
)

add_executable(${EXEC_NAME} ${SOURCE_FILES})

target_include_directories(
    ${EXEC_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_BINARY_DIR}/include
)

target_compile_options(
    ${EXEC_NAME}
    PUBLIC -O3
           -Wall
           -Woverloaded-virtual
           -Wno-unused-function
           -Wmissing-declarations
           -Werror
)

# Option to build tests
option(
    BUILD_TESTS
    "Build the tests"
    OFF
)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
