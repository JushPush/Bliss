FILE(GLOB HEADS
    *.cpp
)

set(FILES ${HEADS})
set(SUBDIRECTORIES "compression")
set(RELATIVE_PATH "src/system/data")

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