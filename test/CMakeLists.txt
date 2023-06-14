# This part of CMakeLists.txt is for when building darling-dmg
# as a standalone FUSE module outside of Darling.
if (NOT DARLING)
  enable_testing()

  find_package(
    Boost COMPONENTS
      unit_test_framework REQUIRED
  )

  add_definitions(-DBOOST_TEST_DYN_LINK ) # -DDEBUG

  set(
    TEST_SOURCES
    test/CacheTest.cpp
  )

  add_executable(
    CacheTest
      ${TEST_SOURCES}
  )

  target_link_libraries(
    CacheTest
      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
      drldmg
  )

  add_test(
    NAME CacheTest
    COMMAND CacheTest
  )
endif(NOT DARLING)
