FILE(GLOB SOURCES
    *.cpp
	*.c
)

set(FILES ${SOURCES})
set(SUBDIRECTORIES "")
set(RELATIVE_PATH "src/graphics")

#Add all subdirectories 
foreach(VAR ${SUBDIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	#Add source files to target
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	
	#Install our source files
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()