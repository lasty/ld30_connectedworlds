cmake_minimum_required(VERSION 3.0)

#
# FindSDL2
# -------
#
# Locate SDL library
#
# Adapted from original FindSDL2
#
# This defines an interface library "sdl2"
# which you can link to using
# target_link_library(program sdl2)
#
#
#
# ::
#
#   SDL2_LIBRARY, the name of the library to link against
#   SDL2_FOUND, if false, do not try to link to SDL
#   SDL2_INCLUDE_DIR, where to find SDL.h
#   SDL2_VERSION_STRING, human-readable string containing the version of SDL
#
#


find_path(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)



if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(SDL2_LIBRARY
  NAMES SDL2
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)



# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSDLmain -lSDL -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)


if(SDL2_INCLUDE_DIR AND EXISTS "${SDL2_INCLUDE_DIR}/SDL_version.h")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_MAJOR "${SDL2_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_MINOR "${SDL2_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_PATCH "${SDL2_VERSION_PATCH_LINE}")
  set(SDL2_VERSION_STRING ${SDL2_VERSION_MAJOR}.${SDL2_VERSION_MINOR}.${SDL2_VERSION_PATCH})
  unset(SDL2_VERSION_MAJOR_LINE)
  unset(SDL2_VERSION_MINOR_LINE)
  unset(SDL2_VERSION_PATCH_LINE)
  unset(SDL2_VERSION_MAJOR)
  unset(SDL2_VERSION_MINOR)
  unset(SDL2_VERSION_PATCH)
endif()


find_package(PackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR VERSION_VAR SDL2_VERSION_STRING)


#Create interface library for convenience

add_library(SDL2 INTERFACE)

target_include_directories(SDL2 SYSTEM INTERFACE ${SDL2_INCLUDE_DIR})

if(MINGW)
	#find_library(mingw32 NAMES mingw32)
	#target_link_libraries(sdl2 INTERFACE mingw32)
endif()


target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARY})

#find_package(Threads)  #TODO Not sure if this is needed?
#target_link_libraries(sdl2 INTERFACE ${THREADS_LIBRARY})


#Installs dll for windows in given DEST directory, under COMPONENT dll
function(SDL2_INSTALL DEST)
	if(WIN32)
		install(FILES ${SDL2_LIBRARY} DESTINATION ${DEST} COMPONENT dll)
	endif(WIN32)
endfunction()


