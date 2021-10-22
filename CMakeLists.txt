# CMakeList.txt : CMake project for LearnOpenGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("LearnOpenGL")
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
add_executable (LearnOpenGL ${SRC_LIST})

# 拷贝文件到输出目录
file(GLOB SHADER_LIST "${PROJECT_SOURCE_DIR}/shaders/*.fs" "${PROJECT_SOURCE_DIR}/shaders/*.vs")
file(GLOB ASSET_LIST "${PROJECT_SOURCE_DIR}/assets/*.*")
file(COPY ${SHADER_LIST} ${ASSET_LIST} DESTINATION ${CMAKE_BINARY_DIR})

execute_process(COMMAND ${LearnOpenGL} -E
copy ${SHADER_LIST}  ${output_required_files},
copy ${ASSET_LIST}  ${COPY_TARGET_DIR}
)

target_link_libraries(
	LearnOpenGL
	glfw3
	opengl32
)

# TODO: Add tests and install targets if needed.
