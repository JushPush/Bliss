function(bliss_copy_module_output targetName targetDir)
	# Prepare directories for library output
	add_custom_command(TARGET ${targetName} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E
		make_directory ${BLISS_DIR_OUTPUT_LIBS}/Debug
	)

	add_custom_command(TARGET ${targetName} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E
		make_directory ${BLISS_DIR_OUTPUT_LIBS}/Release
	)

	if (${MODULE_INFO_HAS_SOURCES})
		# Copy debug library
		# Note: || (exit 0) makes sure these commands succeed even if no library file was generated.
		add_custom_command(TARGET ${targetName} 
			POST_BUILD
			COMMAND $<$<CONFIG:Debug>:${CMAKE_COMMAND}> -E 
			copy 
				$<TARGET_FILE:${targetName}>
				"${BLISS_DIR_OUTPUT_LIBS}/Debug/" || (exit 0)
		)

		# Copy release library
		add_custom_command(TARGET ${targetName} 
			POST_BUILD
			COMMAND $<$<CONFIG:Release>:${CMAKE_COMMAND}> -E 
			copy
				$<TARGET_FILE:${targetName}>
				"${BLISS_DIR_OUTPUT_LIBS}/Release/" || (exit 0)
		)
	endif()
	
	# Function for recursively going through directories.
	# This is necessary because cmake copy takes a directory,
	# and we want to make sure to copy the files to the correct directory.
	function(read_directory curdir)
		set(SOURCE_PATH ${BLISS_DIR_ROOT}/${targetDir}/src/${targetName}/${curdir})
		set(DEST_PATH ${BLISS_DIR_OUTPUT_INCLUDES}/${targetDir}/${curdir})

		# Clear data
		set(files "")

		# Get all files and folders in the current directory
		file(GLOB children 
			LIST_DIRECTORIES true
			RELATIVE ${SOURCE_PATH} 
			${SOURCE_PATH}/*)

		foreach(child ${children})
			# Files can be checked for copying
			if (NOT (IS_DIRECTORY ${SOURCE_PATH}/${child}))
				get_filename_component(CHILD_EXT ${child} EXT)

				# Only copy headers/inl files
				if (CHILD_EXT STREQUAL ".hpp" OR 
					CHILD_EXT STREQUAL ".h")

					# configure_file creates a CMake (configure time) dependency
					# where if the source file changes, the destination file gets updated (in this case copied to)
					configure_file(${SOURCE_PATH}/${child} ${DEST_PATH}/${child} COPYONLY)
				endif()
			# Folders can be recursively looked through for more headers
			else()
				# Skip irrelevant folders
				if (${child} STREQUAL "Debug" OR 
					${child} STREQUAL "Release" OR
					${child} STREQUAL "CMakeFiles" OR 
					${child} STREQUAL "CMakeScripts" OR 
					${child} STREQUAL "${targetName}.dir")
					continue()
				endif()

				# Recursively add directories
				read_directory(${curdir}/${child})
			endif()
		endforeach()
	endfunction()

	# Run the macro on the root folder
	read_directory("")
endfunction()