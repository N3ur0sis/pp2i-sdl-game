# Set the cmake minimum version to 3.22.1
cmake_minimum_required(VERSION 3.22.1)

# Set the name of the project
project(
  PP2I
  VERSION 0.1
  DESCRIPTION "SDL Game for PP2I project"
  LANGUAGES C)


# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all c source files under the src and app directory
file(GLOB_RECURSE APPS "apps/*.c")
file(GLOB_RECURSE SOURCES "src/*.c" )
FILE(COPY assets/ DESTINATION "${CMAKE_BINARY_DIR}/assets")
add_executable(${PROJECT_NAME} ${SOURCES} ${APPS})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -O3 -fsanitize=address -g)

# Add libraries
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)
add_library(cglm SHARED IMPORTED GLOBAL)
add_library(glad STATIC IMPORTED GLOBAL)
add_library(assimp SHARED IMPORTED GLOBAL)
set_target_properties(cglm PROPERTIES  IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/cglm/libcglm.so)
set_target_properties(glad PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/glad/libglad.a)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/assimp/libassimp.so)


# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE libs/cglm/include )
target_include_directories(${PROJECT_NAME} PRIVATE libs/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE libs/assimp/include)

# Add compiler errors/warnings flags
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} -fsanitize=address )
target_link_libraries(${PROJECT_NAME} assimp -fsanitize=address)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} -fsanitize=address)
target_link_libraries(${PROJECT_NAME} cglm -lm  -fsanitize=address)
target_link_libraries(${PROJECT_NAME} glad -fsanitize=address)


