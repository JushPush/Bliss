function(bliss_configure_engine_application target)
	# Language
	target_compile_features(${target} PUBLIC cxx_std_17)
	
	# Dependency on Bliss
	target_include_directories(${target} PUBLIC ${BLISS_INCLUDE_ENGINE})
	target_link_libraries(${target} PUBLIC ${BLISS_LIBS_ENGINE})

	target_include_directories(${target} PUBLIC ${BLISS_INCLUDE_THIRD_PARTY})
	target_link_libraries(${target} PUBLIC ${BLISS_LIBS_THIRD_PARTY})
	
	# Compiler
	target_compile_definitions(${target} PUBLIC ${BLISS_DEFINITIONS})
	target_compile_options(${target} PUBLIC ${BLISS_COMPILER_FLAGS})
	
	# Linker
	if (NOT ${BLISS_LINKER_FLAGS} STREQUAL "")
		target_link_options(${target} PUBLIC ${BLISS_LINKER_FLAGS})
	endif()
	set_target_properties(${target} PROPERTIES LINKER_LANGUAGE ${BLISS_LANGUAGE})
endfunction()