cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(bliss LANGUAGES CXX)

# Config
option(BLISS_FORCE_ENABLE_ALL_MODULES "Force enable all modules" OFF)
option(BLISS_FETCH_MODULES "Enable fetching required modules" ON)

# Folder structure
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set(CMAKE_FOLDER CMakePredefinedTargets)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Dir variables
set(BLISS_DIR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BLISS_DIR_BLISS ${CMAKE_CURRENT_SOURCE_DIR}/bliss)
set(BLISS_DIR_ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/bliss/engine)
# set(BLISS_DIR_EDITOR ${CMAKE_CURRENT_SOURCE_DIR})

set(BLISS_DIR_OUTPUT_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BLISS_DIR_OUTPUT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

# C++ files
set(BLISS_LANGUAGE CXX)
set(BLISS_FILE_TYPES *.h *.hpp *.c *.cpp)

# Include Dirs
set(BLISS_INCLUDE_ALL "")
set(BLISS_INCLUDE_ENGINE "")
set(BLISS_INCLUDE_THIRD_PARTY "")

# Libs
set(BLISS_LIBS_ALL "")
set(BLISS_LIBS_ENGINE "")
set(BLISS_LIBS_THIRD_PARTY "")

# Definitions
set(BLISS_DEFINITIONS "")
list(APPEND BLISS_DEFINITIONS "BLISS_ENGINE")

# Compiler Flags
set(BLISS_COMPILER_FLAGS "")
set(BLISS_LINKER_FLAGS "")

# Force to type static
set(BLISS_LIBRARY_TYPE STATIC)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
mark_as_advanced(FORCE BUILD_SHARED_LIBS) # Hide

include("${CMAKE_MODULE_PATH}/copy_module_output.cmake")
include("${CMAKE_MODULE_PATH}/configure_application.cmake")
include("${CMAKE_MODULE_PATH}/configure_module.cmake")
include("${CMAKE_MODULE_PATH}/find_sources.cmake")

# Git stuff would otherwise go here IDC though

set(BLISS_ENABLED_MODULE_NAMES "")
set(BLISS_ENABLED_MODULE_PATHS "")
add_subdirectory(${BLISS_DIR_BLISS})