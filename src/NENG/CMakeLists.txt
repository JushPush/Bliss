add_library("${PROJECT_NAME}" "")
add_library(NENG::NENG ALIAS "${PROJECT_NAME}")

target_link_libraries("${PROJECT_NAME}" glfw GLEW glut GL GLU)

set(NENG_EXPORT_FILE "NENG-Exports")
install(TARGETS "${PROJECT_NAME}" EXPORT "${NENG_EXPORT_FILE}")

target_include_directories("${PROJECT_NAME}" PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>" #NENG_export.h
	"$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include
)

if(NOT BUILD_SHARED_LIBS)
	set(STATIC_POSTFIX "-s")
	set_target_properties("${PROJECT_NAME}" PROPERTIES 
	COMPILE_FLAGS -DNENG_STATIC_DEFINE)
endif()

#Rename target NENG
set_target_properties("${PROJECT_NAME}" PROPERTIES
	DEBUG_POSTFIX "${STATIC_POSTFIX}-d" 
	RELEASE_POSTFIX "${STATIC_POSTFIX}"
	MINSIZEREL_POSTFIX "${STATIC_POSTFIX}-mr"
	RELWITHDEBINFO_POSTFIX "${STATIC_POSTFIX}-rd"
)

include("GenerateExportHeader")
generate_export_header("${PROJECT_NAME}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/NENG_export.h" DESTINATION "include")


add_subdirectory("include")
add_subdirectory("src")

set(NENG_CONFIG_DIR "lib/cmake/${PROJECT_NAME}")
configure_file("${NENG_SOURCE_DIR}/cmake/NENGConfig.cmake.in" "${NENG_BINARY_DIR}/${NENG_CONFIG_DIR}/NENGConfig.cmake")
install(FILES "${NENG_BINARY_DIR}/${NENG_CONFIG_DIR}/NENGConfig.cmake" DESTINATION "${NENG_CONFIG_DIR}")
install(EXPORT "${NENG_EXPORT_FILE}" DESTINATION "${NENG_CONFIG_DIR}" NAMESPACE "NENG::")