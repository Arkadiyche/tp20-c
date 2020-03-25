cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME MyProject)
cmake_minimum_required(VERSION 3.12)
project(hw_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-pthread  -fopenmp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-pthread")

if ($ENV{COVERAGE})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    message("-- Coverage enable")
else ()
    message("-- Coverage disable")
endif()


find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(project/include)

add_library(nn_naive STATIC
        project/src/matrix.c
        project/src/nn.c
        project/include/matrix.h
        project/include/nn.h)

add_library(nn_opt SHARED
        project/src/matrix_opt.c
        project/src/nn_opt.c
        project/include/matrix_opt.h
        project/include/nn_opt.h)

add_executable(tests_naive
	tests/utils.cpp
        tests/main.cpp)

add_executable(tests_opt
        tests/main.cpp)

add_executable(hw2_naive
        project/src/main.c)

add_executable(hw2_opt
        project/src/main_opt.c)

configure_file(
	"example/layers.txt"
	"${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY
)

configure_file(
	"example/input.txt"
	"${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY
)

target_link_libraries(hw2_naive nn_naive)
target_link_libraries(hw2_opt nn_opt)
target_link_libraries(tests_naive ${GTEST_LIBRARIES} nn_naive)
target_link_libraries(tests_opt ${GTEST_LIBRARIES} Threads::Threads nn_opt)

enable_testing()
add_test(tests_naive "./tests")
add_test(tests_opt "./tests")
