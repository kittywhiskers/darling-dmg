cmake_minimum_required(VERSION 3.12)

project(libdrldmg)

set(
  LIB_SOURCES
  "adc.cpp"
  "AppleDisk.cpp"
  "DMGDecompressor.cpp"
  "DMGDisk.cpp"
  "DMGPartition.cpp"
  "GPTDisk.cpp"
  "Reader.cpp"
  "SubReader.cpp"
)

list(TRANSFORM LIB_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/")

# This part of CMakeLists.txt is for when building darling-dmg
# as a standalone FUSE module outside of Darling.
if (NOT DARLING)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

  include(FindLibXml2)

  find_package(LibXml2 REQUIRED)
  include_directories(${LIBXML2_INCLUDE_DIR})

  SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

  add_library(
    drludif STATIC
  )

  target_sources(
    drludif
      PRIVATE ${LIB_SOURCES}
  )

  target_include_directories(
    drludif
      PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
  )

  target_link_libraries(
    drludif
      -lcrypto
      ${LIBXML2_LIBRARY}
  )
endif()
