cmake_minimum_required (VERSION 2.8)

project (PrezentacjaNaOI)

set (EXECUTABLE_OUTPUT_PATH "${PrezentacjaNaOI_BINARY_DIR}/bin")

set (QT_QMAKE_EXECUTABLE qmake-qt4)

find_package (Qt4 REQUIRED QtGui QtXml)

include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory (src)
