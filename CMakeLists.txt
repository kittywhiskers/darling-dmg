cmake_minimum_required(VERSION 3.12)

project(darling-dmg)

set(
  CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/"
)

add_definitions(-D_FILE_OFFSET_BITS=64)

add_subdirectory(libdrludif)
add_subdirectory(libdrldmg)
add_subdirectory(src)
if (WITH_TESTS)
  add_subdirectory(test)
endif (WITH_TESTS)
