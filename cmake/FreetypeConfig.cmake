cmake_minimum_required(VERSION 3.0)

#Make an interface library for Freetype

find_package(Freetype REQUIRED)

add_library(Freetype INTERFACE)

target_link_libraries(Freetype INTERFACE ${FREETYPE_LIBRARIES})

target_include_directories(Freetype SYSTEM INTERFACE ${FREETYPE_INCLUDE_DIRS})

message("freetype include dirs: ${FREETYPE_INCLUDE_DIRS}") 
#target_compile_definitions(Freetype INTERFACE USE_FREETYPE)

#Installs dll for windows in given DEST directory, under COMPONENT dll
function(FREETYPE_INSTALL DEST)
	if(WIN32)
		find_file(FREETYPE_DLL NAMES libfreetype-6.dll PATH_SUFFIXES bin)

		message(STATUS "found: ${FREETYPE_DLL}")
		install(FILES ${FREETYPE_DLL} DESTINATION ${DEST} COMPONENT dll)
	endif(WIN32)
endfunction()

