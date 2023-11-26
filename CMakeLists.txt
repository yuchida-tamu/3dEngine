cmake_minimum_required(VERSION 3.10)

project(3d-game-engine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the Glad source file
set(GLAD_SOURCE "src/glad.c")

configure_file(src/shaders_paths.h.in ${CMAKE_BINARY_DIR}/src/shaders_paths.h)

# Add the include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/dependencies/include
    ${CMAKE_SOURCE_DIR}/src/headers
)

include_directories(${CMAKE_BINARY_DIR}/src)  # Include the directory with the generated file


# Add the library directories
link_directories(${CMAKE_SOURCE_DIR}/dependencies/library)

# Find and link against GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Find and link against OpenGL
find_package(OpenGL REQUIRED)

# Create the executable
add_executable(3d-game-engine ${SOURCES} ${GLAD_SOURCE})

# Link against GLFW, OpenGL, and other necessary frameworks
target_link_libraries(3d-game-engine PRIVATE glfw ${OPENGL_LIBRARIES} "-framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation")

# Set the output directory for the executable
set_target_properties(3d-game-engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/generated")
