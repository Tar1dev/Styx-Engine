cmake_minimum_required(VERSION 3.20)

project(MaLibGraphique)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/*.cpp)
list(APPEND SOURCES main.cpp)
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} include/*.h*)

add_executable(MaLibGraphique ${SOURCES} ${HEADERS})

# Inclure les dépendances
find_package(OpenGL REQUIRED)

# Ajout des bibliothèques externes
add_subdirectory(3rdparty/GLFW)
add_library(glad STATIC 3rdparty/glad/src/glad.c)
target_include_directories(glad PUBLIC 3rdparty/glad/include)
add_library(stb_image STATIC 3rdparty/stb/stb_image.cpp)
target_include_directories(stb_image PUBLIC 3rdparty/stb)
target_include_directories(MaLibGraphique PUBLIC 3rdparty/glm)

target_include_directories(MaLibGraphique PUBLIC include)

target_link_libraries(MaLibGraphique PUBLIC glfw OpenGL::GL glad stb_image)