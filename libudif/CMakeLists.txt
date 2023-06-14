cmake_minimum_required(VERSION 3.10)

project(darling_udif)

set(
    UDIF_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/adc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AppleDisk.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DMGDecompressor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DMGDisk.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DMGPartition.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/GPTDisk.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Reader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SubReader.cpp
)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	"${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules/")

add_definitions(-D_FILE_OFFSET_BITS=64)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -O0")

include(FindLibXml2)

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

add_library(
    darling_udif STATIC
    "${UDIF_SOURCES}"
)

target_include_directories(
    darling_udif
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src"
    PUBLIC  "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(
    darling_udif -licuuc 
                 -lcrypto 
                 -lz 
                 -lbz2
                 ${LIBXML2_LIBRARY}
)

install(
    TARGETS darling_udif
    DESTINATION lib
)
