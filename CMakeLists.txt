cmake_minimum_required(VERSION 3.12)

project(rwmicro
	VERSION 1.0.0
	LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

# User-facing options
option(RWMICRO_BUILD_TESTS "Build the unit tests in tests/" OFF)
option(RWMICRO_BUILD_APPS "Build the command-line applications in apps/" OFF)
option(RWMICRO_USE_OPENMP "Enable OpenMP support in applications" OFF)

set(DEFAULT_OMP_NUM_THREADS "0" CACHE STRING "Number of OpenMP threads to use at runtime")

# Dependencies
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
endif()

if (RWMICRO_BUILD_TESTS)
	find_package(Catch2 3 QUIET)

	if (NOT Catch2_FOUND)
        include(FetchContent)

        set(CATCH2_GIT_TAG v3.8.1)

        message(STATUS "Fetching Catch2 ${CATCH2_GIT_TAG} from GitHub...")

        FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG ${CATCH2_GIT_TAG}
        )

		FetchContent_MakeAvailable(Catch2)
    endif()
endif()

# Compiler flags
set(RWMICRO_WARNING_FLAGS
	# GCC/Clang
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wconversion>
	# MSVC
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# Build targets
add_subdirectory(src)

if (RWMICRO_BUILD_APPS)
    add_subdirectory(apps)
endif()

if (RWMICRO_BUILD_TESTS)
    add_subdirectory(tests)
endif()
