# Using some new features in CMake version 3 (Interface libraries)
cmake_minimum_required(VERSION 3.0)

# Setup paths for find_package
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Add extra search paths for libraries here (for windows, or custom setups)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/libs)
list(APPEND CMAKE_PREFIX_PATH ../libs ../libs/install)
# list(APPEND CMAKE_PREFIX_PATH ~/Library/Frameworks)


## RPATH and dyload / dynamic linker stuff for mac and linux
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
if(APPLE)
	set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
else()
	set(CMAKE_INSTALL_RPATH "@origin")  #TODO untested on linux 
endif()


# Set up some defaults for variables; less typing on the command line
set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "Install Prefix")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "(Debug|Release|RelWithDebInfo|MinSizeRel)")

# This needs to be below the install prefix settings for it to work
project(ld30)


# Find prerequisites (see /cmake directory for scripts)
find_package(cpp11 REQUIRED)
find_package(SDL2 2.0.0 REQUIRED COMPONENTS image mixer)
find_package(OpenGL CONFIG)
find_package(Freetype CONFIG)
find_package(GLM 0.9.5.1 REQUIRED)


# Sources

file(GLOB SDL_SOURCES src/sdl/*.cpp)
list(APPEND ALL_SOURCES ${SDL_SOURCES})

file(GLOB FREETYPE_SOURCES src/freetype/*.cpp)
list(APPEND ALL_SOURCES ${FREETYPE_SOURCES})

file(GLOB FONT_SOURCES src/font/*.cpp)
list(APPEND ALL_SOURCES ${FONT_SOURCES})


file(GLOB WARMUP_SOURCES src/*.cpp)
list(APPEND ALL_SOURCES ${WARMUP_SOURCES})

# Main target

add_executable(ld30 MACOSX_BUNDLE ${ALL_SOURCES})


#Because 1000 errors scrolling off the screen is extremely helpful *sarcasm sign*
target_compile_options(ld30 PUBLIC
$<$<CXX_COMPILER_ID:GNU>:-fmax-errors=4>
$<$<CXX_COMPILER_ID:Clang>:-ferror-limit=1>)



# Includes and library links
target_include_directories(ld30 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(ld30 PUBLIC cpp11)
target_link_libraries(ld30 PRIVATE all_warnings)
target_link_libraries(ld30 PUBLIC SDL2 OpenGL Freetype GLM)


# Install steps
if(APPLE)
	set(DATA_PATH ld30.app/Contents/Resources)  #TODO find proper app path
	set(FRAMEWORK_PATH ld30.app/Contents/Frameworks)  #TODO find proper app path
else()
	set(DATA_PATH .)
endif()

install(TARGETS ld30 DESTINATION .)

install(DIRECTORY data DESTINATION ${DATA_PATH})

install(FILES README.md DESTINATION .)
file(GLOB SCREENSHOTS *.jpg)
install(FILES ${SCREENSHOTS} DESTINATION .)


# Setup for windows dlls required to be installed
if (WIN32)
	CPP11_INSTALL(.)  #for C/C++ runtime and library
	SDL2_INSTALL(.)
	SDL2_IMAGE_INSTALL(.)
	SDL2_MIXER_INSTALL(.)
	FREETYPE_INSTALL(.)
endif(WIN32)


if (APPLE)
	# im sure there has to be a better way...

	install(DIRECTORY ${SDL2_LIBRARY} DESTINATION ${FRAMEWORK_PATH})
	install(DIRECTORY ${SDL2_IMAGE_LIBRARY} DESTINATION ${FRAMEWORK_PATH})
	install(DIRECTORY ${SDL2_MIXER_LIBRARY} DESTINATION ${FRAMEWORK_PATH})

endif(APPLE)



