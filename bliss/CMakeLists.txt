

execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${BLISS_DIR_OUTPUT_INCLUDES}/)
execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${BLISS_DIR_OUTPUT_LIBS}/)

macro(bliss_add_module NAME PATH DIR)
    #if (NOT ${NAME} STREQUAL "core")
    #    string(TOUPPER ${NAME} VARIABLE_NAME)
    #    option(BLISS_MODULE_${VARIABLE_NAME} "Adds module ${NAME} from the build if enabled" OFF)
    #endif()

    #if ((${NAME} STREQUAL "core") OR
    #    (${BLISS_MODULE_${VARIABLE_NAME}}) OR
    #    (${BLISS_FORCE_ENABLE_ALL_MODULES}))

        message(STATUS: "MODULE: \"${NAME}\" [Enabled]")

        set(MODULE_INFO_HAS_HEADERS OFF)
        set(MODULE_INFO_HAS_SOURCES OFF)
        set(MODULE_INFO_SOURCES "")

        add_subdirectory(${BLISS_DIR_ROOT}/${PATH})
        set_target_properties(${NAME} PROPERTIES FOLDER ${DIR})

        if (${MODULE_INFO_HAS_HEADERS})
			list(APPEND BLISS_INCLUDE_ALL "${BLISS_DIR_ROOT}/${PATH}/src")
			list(APPEND BLISS_INCLUDE_ENGINE "${BLISS_DIR_ROOT}/${PATH}/src")
		endif()

		# We have to check explicitly because otherwise
		# targets will attempt to link with ${NAME}, which won't
		# exist if the target has no cpp or c files
		if (${MODULE_INFO_HAS_SOURCES})
			list(APPEND BLISS_LIBS_ALL ${NAME})
			list(APPEND BLISS_LIBS_ENGINE ${NAME})
		endif()
		
		list(APPEND BLISS_DEFINITIONS "BLISS_${VARIABLE_NAME}")

		list(APPEND BLISS_ENABLED_MODULE_NAMES ${NAME})
		list(APPEND BLISS_ENABLED_MODULE_PATHS ${PATH})
    #else()
    #    message(STATUS "MODULE: \"${NAME}\" [Disabled]")
    #endif()

endmacro()

bliss_add_module("core" "bliss/engine/core" "bliss/engine")
bliss_add_module("graphics" "bliss/engine/graphics" "bliss/engine")

if (NOT ${SUBMODULE_COUNT} EQUAL 0)
	bliss_add_module("core" "bliss/engine/core" "bliss/engine")

	math(EXPR ITER_END "${SUBMODULE_COUNT} - 1")
    foreach(INDEX RANGE 0 ${ITER_END})
        # Get submodule info
        list(GET SUBMODULE_NAMES ${INDEX} SUBMODULE_NAME)
        list(GET SUBMODULE_PATHS ${INDEX} SUBMODULE_PATH)
        list(GET SUBMODULE_DIRS ${INDEX} SUBMODULE_DIR)
        list(GET SUBMODULE_HASHES ${INDEX} SUBMODULE_HASH)

		# Only add modules if they are in the bliss/engine folder
		# Editor modules are added separately based on the engine modules
		string(SUBSTRING ${SUBMODULE_PATH} 0 12 PATH_PREFIX)
		if (NOT ${PATH_PREFIX} STREQUAL "bliss/engine")
			continue()
		endif()

		# Core was added in manually before the for loop
		if (${SUBMODULE_NAME} STREQUAL "core")
			continue()
		endif()

		# Add module
		bliss_add_module(${SUBMODULE_NAME} ${SUBMODULE_PATH} ${SUBMODULE_DIR})
    endforeach()
endif()

foreach(library ${BLISS_LIBS_ENGINE})
    set_target_properties(${library} PROPERTIES LINKER_LANGUAGE ${BLISS_LANGUAGE})

	target_include_directories(${library} PUBLIC ${BLISS_INCLUDE_ENGINE})
	target_compile_definitions(${library} PUBLIC ${BLISS_DEFINITIONS})
	target_compile_options(${library} PUBLIC ${BLISS_COMPILER_FLAGS})
    target_compile_features(${library} PUBLIC cxx_std_17)
	target_link_options(${library} PUBLIC ${BLISS_LINKER_FLAGS})
endforeach()

# Re-set all the modified BLISS variables but with PARENT_SCOPE enabled
# so that it properly updates in the root scope.
set(BLISS_LIBS_ALL ${BLISS_LIBS_ALL} PARENT_SCOPE)
set(BLISS_LIBS_ENGINE ${BLISS_LIBS_ENGINE} PARENT_SCOPE)
set(BLISS_LIBS_THIRD_PARTY ${BLISS_LIBS_THIRD_PARTY} PARENT_SCOPE)

set(BLISS_INCLUDE_ALL ${BLISS_INCLUDE_ALL} PARENT_SCOPE)
set(BLISS_INCLUDE_ENGINE ${BLISS_INCLUDE_ENGINE} PARENT_SCOPE)
set(BLISS_INCLUDE_THIRD_PARTY ${BLISS_INCLUDE_THIRD_PARTY} PARENT_SCOPE)

set(BLISS_DEFINITIONS ${BLISS_DEFINITIONS} PARENT_SCOPE)

set(BLISS_ENABLED_MODULE_NAMES ${BLISS_ENABLED_MODULE_NAMES} PARENT_SCOPE)
set(BLISS_ENABLED_MODULE_PATHS ${BLISS_ENABLED_MODULE_PATHS} PARENT_SCOPE)
