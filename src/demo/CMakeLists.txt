add_executable("DEMO" "main.cpp")
target_link_libraries("DEMO" Bliss::Bliss)

target_include_directories("DEMO" PRIVATE ${PROJECT_SOURCE_DIR}/external/include)
target_link_directories("DEMO" PRIVATE ${PROJECT_SOURCE_DIR}/external/lib)