# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location.

project(ooTests LANGUAGES CXX)

# Dependencies.
find_package(doctest CONFIG REQUIRED)
include(doctest)

# Tests.
add_executable(oo_test src/oo_test.cpp
  src/color.cpp
  src/dimension.cpp
  src/geometry.cpp
  src/log.cpp
  src/terminal.cpp
)

target_compile_features(oo_test PRIVATE cxx_std_20)
target_link_libraries(oo_test PRIVATE oo_lib doctest::doctest)

doctest_discover_tests(oo_test)
