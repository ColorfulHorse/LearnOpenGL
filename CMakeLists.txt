# CMakeList.txt : CMake project for LearnOpenGL, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project("LearnOpenGL")
set(CXX_STANDARD 11)

file(GLOB SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)

# Add source to this project's executable.
add_executable(LearnOpenGL ${SRC_LIST})

file(GLOB SHADER_LIST "${PROJECT_SOURCE_DIR}/shaders/*")
file(GLOB ASSET_LIST "${PROJECT_SOURCE_DIR}/assets/*")

# 编译前拷贝资源文件
add_custom_command(TARGET LearnOpenGL PRE_BUILD
	COMMENT "copy"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	${SHADER_LIST} ${ASSET_LIST} ${CMAKE_BINARY_DIR})

target_link_libraries(
	LearnOpenGL
	glfw3
	opengl32
)

# TODO: Add tests and install targets if needed.
