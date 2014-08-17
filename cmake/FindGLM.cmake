cmake_minimum_required(VERSION 3.0)

#Make an interface library for GLM (OpenGl Mathematics Library)

find_path(GLM_INCLUDE_DIR NAMES glm/glm.hpp)

add_library(GLM INTERFACE)

target_include_directories(GLM SYSTEM INTERFACE ${GLM_INCLUDE_DIR})

#Silence the warning that we know all angles are in radians
#(Might not be necessary in later versions)
target_compile_definitions(GLM INTERFACE GLM_FORCE_RADIANS)

unset(GLM_VERSION_STRING)

foreach(VPART MAJOR MINOR PATCH REVISION)
	file(STRINGS "${GLM_INCLUDE_DIR}/glm/detail/setup.hpp" VERSION_LINE REGEX "^#define[ \t]+GLM_VERSION_${VPART}[ \t]+[0-9]+$")
	string(REGEX REPLACE "^#define[ \t]+GLM_VERSION_${VPART}[ \t]+([0-9]+)$" "\\1" VERSION_LINE ${VERSION_LINE})
	set(GLM_VERSION_STRING "${GLM_VERSION_STRING}${SEP}${VERSION_LINE}")
	set(SEP .)
endforeach()
unset(VERSION_LINE)
unset(SEP)

#message(GLM_VERSION_STRING ${GLM_VERSION_STRING})

find_package(PackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM REQUIRED_VARS GLM_INCLUDE_DIR VERSION_VAR GLM_VERSION_STRING)

