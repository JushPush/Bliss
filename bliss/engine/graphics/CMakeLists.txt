project(graphics LANGUAGES ${BLISS_LANGUAGE})

bliss_find_sources(sources "${PROJECT_SOURCE_DIR}"/src)
add_library(graphics ${BLISS_LIBRARY_TYPE} ${sources})

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "" FORCE)
