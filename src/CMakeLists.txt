file(GLOB_RECURSE RWMICRO_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(RWMicro ${RWMICRO_SOURCES})

target_include_directories(RWMicro PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(RWMicro PUBLIC cxx_std_17)

target_compile_options(RWMicro PUBLIC
    ${RWMICRO_WARNING_FLAGS}
)
