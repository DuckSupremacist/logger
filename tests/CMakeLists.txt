include(FetchContent)

# Enable testing
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/release-1.11.0.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ######################################################################################################################

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
)

set(LIBRARIES stdc++fs)

file(
    GLOB_RECURSE
    TESTED_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
list(
    FILTER
    TESTED_SOURCES
    EXCLUDE
    REGEX
    ".*/main\\.cpp$"
)

# Compile common sources to object files
add_library(
    common_objects
    OBJECT
    ${TESTED_SOURCES}
)
target_link_libraries(
    common_objects
    ${LIBRARIES}
)
link_libraries(
    gtest
    gtest_main
    ${LIBRARIES}
)

#add_executable(
#    test-ecc
#    $<TARGET_OBJECTS:common_objects>
#    src/fsm.test.cpp
#)

# Add the tests to be run
#gtest_discover_tests(test-fsm)
