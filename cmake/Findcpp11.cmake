
cmake_minimum_required(VERSION 3.0)

# Easy way to apply compiler options
# use like:
# target_link_library(program cpp11) 


add_library(cpp11 INTERFACE)

target_compile_options(cpp11 INTERFACE
	$<$<CXX_COMPILER_ID:GNU>:-std=c++11>
	$<$<CXX_COMPILER_ID:Clang>:-std=c++11>
	$<$<CXX_COMPILER_ID:AppleClang>:-std=c++11>
	#TODO not sure about other compilers
)


add_library(all_warnings INTERFACE)

target_compile_options(all_warnings INTERFACE
	$<$<CXX_COMPILER_ID:GNU>:-Wall>
	$<$<CXX_COMPILER_ID:Clang>:-Wall>
	$<$<CXX_COMPILER_ID:AppleClang>:-std=c++11>
	#TODO not sure about other compilers
)


#Installs dlls for windows in given DEST directory, under COMPONENT dll
function(CPP11_INSTALL DEST)
	if(WIN32)

		#add any variants of dlls to this list (it will not break if they are not found)
		list(APPEND dllnames libgcc_s_seh-1.dll libstdc++-6.dll)

		foreach(dll ${dllnames})
			find_file(DLL_FILE NAMES ${dll})

			if(DLL_FILE)
				message(STATUS "found: ${DLL_FILE}")
				install(FILES ${DLL_FILE} DESTINATION ${DEST} COMPONENT dll)
			endif()
			unset(DLL_FILE CACHE) #so much for contained scope inside a function
		endforeach()

	endif(WIN32)
endfunction()

