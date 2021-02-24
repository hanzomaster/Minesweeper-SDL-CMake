cmake_minimum_required(VERSION 3.19)
project(SDL2 VERSION 1.0.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(SDL2_PATH "SDL2")
set(SDL2_IMAGE_PATH "SDL2")
set(SDL2_TTF_PATH "SDL2")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(
	${SDL2_INCLUDE_DIR} 
	${SDL2_IMAGE_INCLUDE_DIRS} 
	${SDL2_TTF_INCLUDE_DIR})
set(SOURCES
	src/main.cpp
	src/Button.cpp
	src/Texture.cpp
	src/Variables.cpp
	)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(
	${PROJECT_NAME}
	${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)