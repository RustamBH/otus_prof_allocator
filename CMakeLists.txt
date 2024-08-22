cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(
	Allocator	
	main.cpp
	logging_allocator.h
	MyContainer.h
	pretty.h
)

set_target_properties(Allocator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
