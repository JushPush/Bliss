add_executable("DEMO" "main.cpp")

target_include_directories("DEMO" PRIVATE ${PROJECT_SOURCE_DIR}/external/include)
target_link_directories("DEMO" PRIVATE ${PROJECT_SOURCE_DIR}/external/lib)

target_include_directories("DEMO" PRIVATE ${PROJECT_SOURCE_DIR}/include/bliss/engine)
target_link_directories("DEMO" PRIVATE ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries("DEMO" GLEW GL X11 pthread SDL2main SDL2)