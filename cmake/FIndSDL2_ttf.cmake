find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
        HINTS
        ENV SDL2TTFDIR
        ENV SDL2DIR
        PATH_SUFFIXES SDL2
        # path suffixes to search inside ENV{SDLDIR}
        include/SDL2 include
        PATHS ${SDL2_TTF_PATH}
        )

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VC_LIB_PATH_SUFFIX lib/x64)
else ()
    set(VC_LIB_PATH_SUFFIX lib/x86)
endif ()

find_library(SDL2_TTF_LIBRARY
        NAMES SDL2_ttf
        HINTS
        ENV SDL2TTFDIR
        ENV SDL2DIR
        PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
        PATHS ${SDL2_TTF_PATH}
        )

if (SDL2_TTF_INCLUDE_DIR AND EXISTS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h")
    file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_TTF_INCLUDE_DIR}/SDL_ttf.h" SDL2_TTF_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+[0-9]+$")
    string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MAJOR "${SDL2_TTF_VERSION_MAJOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_TTF_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_MINOR "${SDL2_TTF_VERSION_MINOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL_TTF_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_TTF_VERSION_PATCH "${SDL2_TTF_VERSION_PATCH_LINE}")
    set(SDL2_TTF_VERSION_STRING ${SDL2_TTF_VERSION_MAJOR}.${SDL2_TTF_VERSION_MINOR}.${SDL2_TTF_VERSION_PATCH})
    unset(SDL2_TTF_VERSION_MAJOR_LINE)
    unset(SDL2_TTF_VERSION_MINOR_LINE)
    unset(SDL2_TTF_VERSION_PATCH_LINE)
    unset(SDL2_TTF_VERSION_MAJOR)
    unset(SDL2_TTF_VERSION_MINOR)
    unset(SDL2_TTF_VERSION_PATCH)
endif ()

set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_ttf
        REQUIRED_VARS SDL2_TTF_LIBRARIES SDL2_TTF_INCLUDE_DIRS
        VERSION_VAR SDL2_TTF_VERSION_STRING)

# for backward compatibility
set(SDLTTF_LIBRARY ${SDL2_TTF_LIBRARIES})
set(SDLTTF_INCLUDE_DIR ${SDL2_TTF_INCLUDE_DIRS})
set(SDLTTF_FOUND ${SDL2_TTF_FOUND})