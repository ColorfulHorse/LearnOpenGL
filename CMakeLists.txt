cmake_minimum_required(VERSION 3.8)

project("LearnOpenGL")
set(CXX_STANDARD 11)

file(GLOB_RECURSE SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c")

set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${LIBS_DIR})

add_executable(LearnOpenGL ${SRC_LIST})

file(GLOB_RECURSE LIB_LIST ${LIBS_DIR}/*.dll)

# 链接前拷贝资源文件
add_custom_command(TARGET LearnOpenGL PRE_LINK
	COMMENT "copy ${LIB_LIST}"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	${LIB_LIST} ${OUTPUT_DIR})

target_link_libraries(
	LearnOpenGL
	assimp
	glfw3
	opengl32
)
