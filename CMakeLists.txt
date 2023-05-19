
cmake_minimum_required(VERSION 3.0)
include(CMakePrintHelpers)
project(LedInterfaceFramework CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread")

file (GLOB_RECURSE LedInterfaceFramework_SOURCES CONFIGURE_DEPENDS "Projects/*.cpp")
file (GLOB_RECURSE LedInterfaceFramework_HEADERS CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR} "Projects/*/*.h")

file (COPY PythonScripts DESTINATION ${CMAKE_BINARY_DIR})	
file (COPY ConfigFiles DESTINATION ${CMAKE_BINARY_DIR})

# Finds all header file folders
set (LedInterfaceFramework_INCLUDE_DIRS "")
foreach (_headerFile ${LedInterfaceFramework_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND LedInterfaceFramework_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES LedInterfaceFramework_INCLUDE_DIRS)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

#cmake_print_variables(LedInterfaceFramework_SOURCES LedInterfaceFramework_HEADERS LedInterfaceFramework_INCLUDE_DIRS)

add_executable(${PROJECT_NAME} ${LedInterfaceFramework_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${LedInterfaceFramework_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Libraries)
target_link_directories(${PROJECT_NAME} PRIVATE ${Python3_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})

