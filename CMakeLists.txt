cmake_minimum_required(VERSION 3.20)

project(MaLibGraphique)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE GAME_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} game/src/*.cpp)
file(GLOB_RECURSE PLATFORM_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} platform/src/*.cpp)

add_executable(MaLibGraphique ${GAME_SOURCES} ${PLATFORM_SOURCES})

target_include_directories(MaLibGraphique PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/game/include")
target_include_directories(MaLibGraphique PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/platform/include")

add_compile_definitions(RESSOURCES_DIR="${CMAKE_SOURCE_DIR}/ressources")


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