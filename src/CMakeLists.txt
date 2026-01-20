set(HEADER_LIST
        "${HexapodUtilsLibrary_SOURCE_DIR}/include/ring_buffer.h"
)

add_library(HexapodUtils
   ring_buffer.c
    log.c
)

target_include_directories(HexapodUtils
        PUBLIC ../include 
        PRIVATE ../priv_include
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Enable coverage for Debug builds
    target_compile_options(HexapodUtils PRIVATE "$<$<CONFIG:DEBUG>:--coverage>")
    target_link_options(HexapodUtils PRIVATE "$<$<CONFIG:DEBUGB>:--coverage>")
endif()


source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
