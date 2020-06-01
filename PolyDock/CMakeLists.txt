cmake_minimum_required(VERSION 3.1.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

##
# Function that generates source groups
##
function(GenerateSourceGoups Sources)
	foreach(Source ${Sources})
		get_filename_component(SourcePath "${Source}" PATH)
		if (WIN32)
			string(REPLACE "/" "\\" SourcePath "${SourcePath}")
		endif()
		source_group("${SourcePath}" FILES "${Source}")
	endforeach()
endfunction()

##
# Start
##
project(PolyDock VERSION "1.0.0")

set(POLYDOCK_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(DIST_DIR "${POLYDOCK_ROOT_DIR}/../Dist")
set(COMMON_BUILD_DIR "${POLYDOCK_ROOT_DIR}/../CommonBuild")

# Output dirs
if (WIN32)
	set(FULL_DIST_DIR "${DIST_DIR}") # Config name is added autmatically on windows
else()
	set(FULL_DIST_DIR "${DIST_DIR}/${BUILD_CONFIG_NAME}")
endif()
	
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FULL_DIST_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FULL_DIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FULL_DIST_DIR})

# C++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For CI MSVC need additional flag
if(MSVC)
    set(CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) /std:c++17")
endif(MSVC)

# Find externals
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(EnTT 3.3 REQUIRED)
find_package(Eigen3 3.3 REQUIRED)

# Add our targets
set(POLYDOCK_TARGET PolyDock)
set(TEST_APP_TARGET TestApp)

add_subdirectory(PolyDock)
add_subdirectory(TestApp)

#################################################
# installation instructions
#################################################
install(TARGETS ${POLYDOCK_TARGET}
    EXPORT ${POLYDOCK_TARGET}_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${POLYDOCK_TARGET}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(EXPORT ${POLYDOCK_TARGET}_Targets
    FILE ${POLYDOCK_TARGET}Targets.cmake
    NAMESPACE ${POLYDOCK_TARGET}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${POLYDOCK_TARGET}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${POLYDOCK_TARGET}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${POLYDOCK_TARGET}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/PolyDock/src/pd DESTINATION include)