cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(oo LANGUAGES CXX)

include(cmake/variables.cmake)

# ccache
find_program(CCACHE_BINARY NAMES ccache)

if(CCACHE_BINARY)
  message(STATUS "${CCACHE_BINARY} found and enabled")
  set(CMAKE_CXX_COMPILER_LAUNCHER
    ${CCACHE_BINARY}
    CACHE FILEPATH "CXX compiler cache used")
endif()

# Dependencies.
find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

# Declare library.
add_library(
  oo_lib OBJECT
  src/action.cpp
  src/action.hpp
  src/colonist.cpp
  src/colonist.hpp
  src/color.hpp
  src/dimension.hpp
  src/energy.hpp
  src/game.cpp
  src/game.hpp
  src/graphics_backend.hpp
  src/input_manager.cpp
  src/input_manager.hpp
  src/log.cpp
  src/log.hpp
  src/map.cpp
  src/map.hpp
  src/point.hpp
  src/rng.cpp
  src/rng.hpp
  src/sdl_backend.cpp
  src/sdl_backend.hpp
  src/terminal.cpp
  src/terminal.hpp
  src/tile.hpp
)

target_compile_features(oo_lib PUBLIC cxx_std_20)

target_include_directories(
  oo_lib ${warning_guard}
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

target_link_libraries(oo_lib
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
  PUBLIC
  fmt::fmt)

# Declare executable.
add_executable(oo_exe src/main.cpp)
add_executable(oo::exe ALIAS oo_exe)
set_target_properties(oo_exe PROPERTIES OUTPUT_NAME oo)
target_compile_features(oo_exe PRIVATE cxx_std_20)
target_link_libraries(oo_exe PRIVATE oo_lib)

add_custom_command(
  TARGET oo_exe
  POST_BUILD
  COMMAND
  ${CMAKE_COMMAND} -E create_symlink
  "$<TARGET_PROPERTY:oo_exe,SOURCE_DIR>/data"
  "$<TARGET_PROPERTY:oo_exe,BINARY_DIR>/data"
  VERBATIM
)

# Developer mode.
if(NOT oo_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of oo"
  )
endif()

include(cmake/dev-mode.cmake)
