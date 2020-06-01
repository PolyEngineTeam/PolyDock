# Include dir
set(POLYDOCK_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/src)
set(POLYDOCK_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/res)

# Source files list
file(GLOB_RECURSE POLYDOCK_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} 
    ${POLYDOCK_INCLUDE}/*.ui 
    ${POLYDOCK_INCLUDE}/*.cpp 
    ${POLYDOCK_INCLUDE}/*.hpp 
    ${POLYDOCK_INCLUDE}/*.h)
file(GLOB_RECURSE POLYDOCK_RES RELATIVE ${CMAKE_CURRENT_LIST_DIR} 
    ${POLYDOCK_RESOURCES}/*.qrc)
GenerateSourceGoups("${POLYDOCK_SRCS}")
GenerateSourceGoups("${POLYDOCK_RES}")

# Qt variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOUIC_SEARCH_PATHS Form)
set(Qt5_DIR $ENV{POLY_QTDIR})
list(APPEND CMAKE_PREFIX_PATH $ENV{POLY_QTDIR})

add_library(${POLYDOCK_TARGET} STATIC ${POLYDOCK_SRCS} ${POLYDOCK_RES} ${AUTOGEN_SOURCE_GROUP})
target_include_directories(${POLYDOCK_TARGET} PUBLIC 
                                              $<BUILD_INTERFACE:${POLYDOCK_INCLUDE}>
                                              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Link externals
target_link_libraries(${POLYDOCK_TARGET} Qt5::Widgets Qt5::Core)
target_link_libraries(${POLYDOCK_TARGET} EnTT::EnTT)
target_link_libraries(${POLYDOCK_TARGET} Eigen3::Eigen)