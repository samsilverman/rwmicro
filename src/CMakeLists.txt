set(RWMICRO_SOURCES
    grid.cpp
    grow.cpp
    has_valid_boundary.cpp
    has_valid_connectivity.cpp
    save.cpp
    validate.cpp
)

add_library(rwmicro ${RWMICRO_SOURCES})

target_include_directories(rwmicro PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(rwmicro PRIVATE ${RWMICRO_WARNING_FLAGS})
