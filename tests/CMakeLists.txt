cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

add_executable(rwmicro_tests ${TEST_SOURCES})

target_link_libraries(rwmicro_tests PRIVATE
    rwmicro
    Catch2::Catch2WithMain
)

target_compile_options(rwmicro_tests PRIVATE ${RWMICRO_WARNING_FLAGS})
