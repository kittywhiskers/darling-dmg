# This part of CMakeLists.txt is for when building darling-dmg
# as a standalone FUSE module outside of Darling.
if(NOT DARLING)
  add_executable(darling-dmg
    main-fuse.cpp
  )

  target_link_libraries(darling-dmg -lfuse drldmg)
  install(TARGETS darling-dmg RUNTIME DESTINATION bin)
endif(NOT DARLING)

# This is used in Darling build.
if(DARLING)
  include(wrap_elf)
  include(darling_exe)
  include(FindPkgConfig)

  add_definitions(-DCOMPILE_WITH_LZFSE=1)

  pkg_check_modules(FUSE REQUIRED fuse)

  include_directories(
    ${FUSE_INCLUDE_DIRS}
  )

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -nostdinc")

  wrap_elf(fuse libfuse.so)

  add_darling_executable(hdiutil
    ${LIB_SOURCES}
    src/main-hdiutil.cpp
  )

  target_link_libraries(
    hdiutil
      fuse
      icucore
      z
      bz2
      crypto44
      xml2
      iconv
      lzfse
  )
  
  install(TARGETS hdiutil DESTINATION libexec/darling/usr/bin)
endif(DARLING)
