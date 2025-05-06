cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME polynoms)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Debug)

file(GLOB polynoms_hdrs "include/polynoms/*.h")
file(GLOB polynoms_srcs "include/polynoms/*.cpp")
file(GLOB main_srcs "src/main.cpp")

add_library(cyclic_list INTERFACE)
target_include_directories(cyclic_list INTERFACE include/cyclic_list)

add_library(polynoms ${polynoms_srcs} ${polynoms_hdrs})
target_include_directories(polynoms PUBLIC include/polynoms)
target_link_libraries(polynoms PUBLIC cyclic_list)

add_executable(main ${main_srcs})
target_link_libraries(main PRIVATE cyclic_list polynoms)

include(CTest)
enable_testing()

if (BUILD_TESTING)
	message(STATUS "Building tests")

	add_library(gtest STATIC gtest/gtest-all.cc)
	target_include_directories(gtest PUBLIC gtest)
	
	if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    		${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    		(${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    		set(pthread "-pthread")
			target_link_libraries(gtest INTERFACE ${pthread})
	endif()

	file(GLOB_RECURSE tests_files "test/*.cpp")
	add_executable(polynoms_test ${tests_files})
	target_link_libraries(polynoms_test PRIVATE gtest cyclic_list polynoms) 

else()
	message(STATUS "Skipping tests")
endif()

# REPORT
message( STATUS "")
message( STATUS "Configuration for ${PROJECT_NAME}")
message( STATUS "====================================")
message( STATUS "  Build type:      ${CMAKE_BUILD_TYPE}")
message( STATUS "  Build tests:     ${BUILD_TESTING}")
message( STATUS "  C++ Standard:    ${CMAKE_CXX_STANDARD}")
message( STATUS "")