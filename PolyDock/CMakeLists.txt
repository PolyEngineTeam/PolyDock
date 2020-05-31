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
# Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# EnTT
add_subdirectory(ThirdParty/entt)
set_target_properties (entt_aob PROPERTIES FOLDER "ThirdParty/entt")

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