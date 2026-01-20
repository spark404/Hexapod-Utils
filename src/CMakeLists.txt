set(HEADER_LIST 
        "${HexapodUtilsLibrary_SOURCE_DIR}/include/ring_buffer.h"
)

add_library(hexapodutils
   ring_buffer.c
)

target_include_directories(hexapodutils 
        PUBLIC ../include 
        PRIVATE ../priv_include
)

# Enable coverage for Debug builds
target_compile_options(hexapodutils PRIVATE "$<$<CONFIG:DEBUG>:--coverage>")
target_link_options(hexapodutils PRIVATE "$<$<CONFIG:DEBUGB>:--coverage>")

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
