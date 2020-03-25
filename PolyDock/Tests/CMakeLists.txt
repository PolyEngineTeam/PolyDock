# Root include dir
set(TESTS_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/src)

# Source files list
file(GLOB_RECURSE TESTS_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} 
    ${TESTS_INCLUDE}/*.cpp 
    ${TESTS_INCLUDE}/*.hpp 
    ${TESTS_INCLUDE}/*.h)
GenerateSourceGoups("${TESTS_SRCS}")

add_executable(${TESTS_TARGET} "${TESTS_SRCS}")
target_include_directories(${TESTS_TARGET} PUBLIC ${TESTS_INCLUDE})

# Link externals
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    target_link_libraries(${TESTS_TARGET} gmock_maind)
else (CMAKE_BUILD_TYPE EQUAL "RELEASE")
    target_link_libraries(${TESTS_TARGET} gmock_main)
endif ()

target_link_libraries(${TESTS_TARGET} ${POLYDOCK_TARGET})