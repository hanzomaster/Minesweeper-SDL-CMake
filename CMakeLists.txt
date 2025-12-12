cmake_minimum_required(VERSION 3.19)
project(Minesweeper VERSION 1.0.0 LANGUAGES CXX)

# Require C++11 for constexpr and modern features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Custom CMake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Platform-specific SDL2 path hints (for local SDL2 installation)
if(WIN32)
    set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2" CACHE PATH "SDL2 library path")
    set(SDL2_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2" CACHE PATH "SDL2_image library path")
    set(SDL2_TTF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2" CACHE PATH "SDL2_ttf library path")
    set(SDL2_MIXER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2" CACHE PATH "SDL2_mixer library path")
endif()

# Find SDL2 and related libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/Logic.cpp
    src/Texture.cpp
    src/Variables.cpp
    src/StartScreen.cpp
    src/Clock.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Platform-specific settings
if(WIN32)
    # Hide console window on Windows for Release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    endif()
elseif(APPLE)
    # macOS specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )
endif()

# Copy resources to build directory (optional, for easier debugging)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Images $<TARGET_FILE_DIR:${PROJECT_NAME}>/Images
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sound $<TARGET_FILE_DIR:${PROJECT_NAME}>/Sound
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Font $<TARGET_FILE_DIR:${PROJECT_NAME}>/Font
    COMMENT "Copying resources to build directory"
)
