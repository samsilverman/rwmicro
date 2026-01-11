function(add_app target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE RWMicro)
endfunction()

add_app(1_SingleDesign 1_SingleDesign/1_SingleDesign.cpp)
add_app(2_BatchedDesigns 2_BatchedDesigns/2_BatchedDesigns.cpp)

set(DEFAULT_OMP_NUM_THREADS "0" CACHE STRING "Number of OpenMP threads to use at runtime")

if (RWMICRO_USE_OPENMP)
	find_package(OpenMP REQUIRED COMPONENTS CXX)

    if(DEFAULT_OMP_NUM_THREADS MATCHES "^[0-9]+$")
		if (${DEFAULT_OMP_NUM_THREADS} GREATER 0)
			message(STATUS "OpenMP thread count set to ${DEFAULT_OMP_NUM_THREADS}")
			add_compile_definitions(DEFAULT_OMP_NUM_THREADS=${DEFAULT_OMP_NUM_THREADS})
		endif()
	else()
  		message(FATAL_ERROR "DEFAULT_OMP_NUM_THREADS must be a nonnegative integer")
	endif()

    target_link_libraries(2_BatchedDesigns PRIVATE
        OpenMP::OpenMP_CXX
    )
endif()
