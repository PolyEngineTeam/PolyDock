# Include dir
set(TEST_APP_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/src)

# Source files list
file(GLOB_RECURSE TEST_APP_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} 
    ${TEST_APP_INCLUDE}/*.ui 
    ${TEST_APP_INCLUDE}/*.qrc 
    ${TEST_APP_INCLUDE}/*.cpp 
    ${TEST_APP_INCLUDE}/*.hpp 
    ${TEST_APP_INCLUDE}/*.h)
GenerateSourceGoups("${TEST_APP_SRCS}")

# Qt variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOUIC_SEARCH_PATHS Form)
set(Qt5_DIR $ENV{POLY_QTDIR})
list(APPEND CMAKE_PREFIX_PATH $ENV{POLY_QTDIR})

add_executable(${TEST_APP_TARGET} ${TEST_APP_SRCS} ${AUTOGEN_SOURCE_GROUP})
target_include_directories(${TEST_APP_TARGET} PUBLIC ${TEST_APP_INCLUDE})

# Link externals
target_link_libraries(${TEST_APP_TARGET} Qt5::Widgets Qt5::Core)
target_link_libraries(${TEST_APP_TARGET} ${POLYDOCK_TARGET})