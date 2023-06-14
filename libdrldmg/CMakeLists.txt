cmake_minimum_required(VERSION 3.12)

project(libdrldmg)

set(
  LIB_SOURCES
  "CacheZone.cpp"
  "CachedReader.cpp"
  "FileReader.cpp"
  "HFSAttributeBTree.cpp"
  "HFSBTree.cpp"
  "HFSCatalogBTree.cpp"
  "HFSExtentsOverflowBTree.cpp"
  "HFSFork.cpp"
  "HFSHighLevelVolume.cpp"
  "HFSVolume.cpp"
  "HFSZlibReader.cpp"
  "MacBinary.cpp"
  "MemoryReader.cpp"
  "ResourceFork.cpp"
  "unichar.cpp"
)

list(TRANSFORM LIB_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/")

# This part of CMakeLists.txt is for when building darling-dmg
# as a standalone FUSE module outside of Darling.
if (NOT DARLING)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -O0 -fPIC")

  add_library(
    drldmg SHARED
  )

  target_sources(
    drldmg
      PRIVATE ${LIB_SOURCES}
  )

  target_include_directories(
    drldmg
      PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
  )

  target_link_libraries(
    drldmg
      -lbz2
      -licuuc
      -lz
      drludif
  )

  install(TARGETS drldmg DESTINATION lib)
endif(NOT DARLING)
