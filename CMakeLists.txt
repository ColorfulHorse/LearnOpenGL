# CMakeList.txt : CMake project for LearnOpenGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("LearnOpenGL")
set(CXX_STANDARD 11)

file(GLOB SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)

# Add source to this project's executable.
add_executable (LearnOpenGL ${SRC_LIST})

target_link_libraries(
	LearnOpenGL
	glfw3
	opengl32
)

# TODO: Add tests and install targets if needed.
