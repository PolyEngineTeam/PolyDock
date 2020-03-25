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
project(PolyDock)

set(POLYDOCK_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(DIST_DIR "${POLYDOCK_ROOT_DIR}/dist")
set(COMMON_BUILD_DIR "${POLYDOCK_ROOT_DIR}/commonBuild")

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

# Find externals
# Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# EnTT
add_subdirectory(ThirdParty/entt)
set_target_properties (aob PROPERTIES FOLDER "ThirdParty/entt")

# GSL
add_subdirectory(ThirdParty/eigen)
set_target_properties (uninstall PROPERTIES FOLDER "ThirdParty/eigen")

# GSL
add_subdirectory(ThirdParty/gsl)

# gtest & gmock
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(ThirdParty/gtest)
set_target_properties (gtest PROPERTIES FOLDER "ThirdParty/gtest")
set_target_properties (gtest_main PROPERTIES FOLDER "ThirdParty/gtest")
set_target_properties (gmock PROPERTIES FOLDER "ThirdParty/gtest")
set_target_properties (gmock_main PROPERTIES FOLDER "ThirdParty/gtest")

# Add our targets
set(POLYDOCK_TARGET PolyDock)
set(TEST_APP_TARGET TestApp)
set(TESTS_TARGET Tests)

add_subdirectory(PolyDock)
add_subdirectory(TestApp)
add_subdirectory(Tests)
