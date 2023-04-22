
cmake_minimum_required(VERSION 3.0)

project(LedInterfaceFramework CXX)

set(CMAKE_CXX_STANDARD 20)

file (GLOB_RECURSE LedInterfaceFramework_SOURCES CONFIGURE_DEPENDS "Projects/Source/*/*.cpp")
file (GLOB_RECURSE LedInterfaceFramework_HEADERS CONFIGURE_DEPENDS "Projects/Source/*/Include/*.h")
file (GLOB_RECURSE LedInterfaceFramework_INCLUDE_DIRS CONFIGURE_DEPENDS "Projects/Source/*/Include/")
file (COPY PythonScripts DESTINATION ${CMAKE_BINARY_DIR})	
# Finds all header file folders
#set (LedInterfaceFramework_INCLUDE_DIRS "")
#foreach (_headerFile ${LedInterfaceFramework_HEADERS})
#	get_filename_component(_dir ${_headerFile} PATH)
#	list (APPEND LedInterfaceFramework_INCLUDE_DIRS ${_dir})
#endforeach()
#list (REMOVE_DUPLICATES LedInterfaceFramework_INCLUDE_DIRS)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_executable(LedInterfaceFramework Projects/main.cpp ${LedInderfaceFramework_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${LedInterfaceFramework_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${Python3_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})



