include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_custom_target(
  run
  COMMAND oo_exe
  VERBATIM)

add_dependencies(run oo_exe)
