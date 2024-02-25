# Set the cmake minimum version to 3.22.1
cmake_minimum_required(VERSION 3.22.1)

# Set the name of the project
project(pp2i)


# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all c source files under the src directory
file(GLOB_RECURSE SOURCES "src/Engine/*.c")
file(GLOB DATA "src/DataStructures/*.c")
add_executable(${PROJECT_NAME} ${SOURCES} ${DATA})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)


# Add SDL2 library
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

add_subdirectory(dependencies/glad/)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(dependencies/cglm/)
target_link_libraries(${PROJECT_NAME} -lm cglm_headers)

add_executable(TreeTest src/DataStructures/tests/TreeTest.c src/DataStructures/Tree.c src/DataStructures/Data.c src/DataStructures/Vector.c)
target_compile_options(TreeTest PRIVATE -Wall -Wextra -pedantic -Werror -g)

add_executable(VectorTest src/DataStructures/tests/VectorTest.c src/DataStructures/Vector.c src/DataStructures/Data.c)
target_compile_options(VectorTest PRIVATE -Wall -Wextra -pedantic -Werror -g)

enable_testing()
add_test(NAME TreeTest COMMAND TreeTest)
add_test(NAME VectorTest COMMAND VectorTest)