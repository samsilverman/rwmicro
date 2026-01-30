function(add_app target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE rwmicro)
	target_compile_options(${target} PRIVATE ${RWMICRO_WARNING_FLAGS})
endfunction()

add_app(1_SingleDesign 1_SingleDesign/1_SingleDesign.cpp)
add_app(2_BatchedDesigns 2_BatchedDesigns/2_BatchedDesigns.cpp)

if(RWMICRO_USE_OPENMP)
    target_link_libraries(2_BatchedDesigns PRIVATE OpenMP::OpenMP_CXX)
endif()
