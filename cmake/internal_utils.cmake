function(x_define_compile_macros)
  message("x_define_compile_macros called")
  foreach(m ${ARGN})
    if (${CMAKE_VERSION} VERSION_LESS 3.12)
      add_definitions(-D"${m}")
    else()
      add_compile_definitions(${m})
    endif()
  endforeach()
endfunction()

function(x_check_platform)
  message("CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")

  if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    x_define_compile_macros(__PLATFORM_OS_WINDOWS)
  endif()

endfunction()