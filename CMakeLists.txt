cmake_minimum_required(VERSION 3.8)

project("LearnOpenGL")
set(CXX_STANDARD 11)

file(GLOB_RECURSE SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/output")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")


include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable(LearnOpenGL ${SRC_LIST})

# file(GLOB_RECURSE SHADER_LIST "${PROJECT_SOURCE_DIR}/shaders/*")
# file(GLOB_RECURSE ASSET_LIST "${PROJECT_SOURCE_DIR}/assets/*")

# 链接前拷贝资源文件
# add_custom_command(TARGET LearnOpenGL PRE_LINK
# 	COMMENT "copy ${SHADER_LIST}"
# 	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
# 	${SHADER_LIST} ${ASSET_LIST} "${CMAKE_BINARY_DIR}/output/")

# 链接前拷贝资源文件
add_custom_command(TARGET LearnOpenGL PRE_BUILD
	COMMENT "copy_dictionary"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${PROJECT_SOURCE_DIR}/shaders" "${OUTPUT_DIR}/shaders")

add_custom_command(TARGET LearnOpenGL PRE_BUILD
	COMMENT "copy_dictionary"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${PROJECT_SOURCE_DIR}/assets" "${OUTPUT_DIR}/assets")

target_link_libraries(
	LearnOpenGL
	glfw3
	opengl32
)
