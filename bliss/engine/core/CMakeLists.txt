project(core LANGUAGES ${BLISS_LANGUAGE})

bliss_find_sources(sources "${PROJECT_SOURCE_DIR}"/srcc)
add_library(core ${BLISS_LIBRARY_TYPE} ${sources})

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "" FORCE)

bliss_configure_module(core)
bliss_copy_module_output(core bliss/engine/core)