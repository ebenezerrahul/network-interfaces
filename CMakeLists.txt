cmake_minimum_required(VERSION 4.0)

project(network-interfaces VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
	add_compile_options(-g -O0)
	add_compile_options(-fsanitize=address)
	add_compile_options(-Wall -Wextra)
	add_link_options(-fsanitize=address)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_compile_options(-g -O2)
endif()


add_executable(vpn)

target_sources(
	vpn
	PRIVATE 
	src/main.cpp
)

