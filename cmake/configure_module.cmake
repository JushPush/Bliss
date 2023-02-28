macro(bliss_configure_module module)
    set(MODULE_INFO_HAS_HEADERS OFF PARENT_SCOPE)
    set(MODULE_INFO_HAS_SOURCES OFF PARENT_SCOPE)

    get_target_property(MODULE_SOURCES ${module} SOURCES)
    set(MODULE_INFO_SOURCES ${MODULE_SOURCES} PARENT_SCOPE)

    foreach(src ${MODULE_SOURCES})
        get_filename_component(SRC_EXT ${src} EXT)

        if (SRC_EXT STREQUAL ".hpp" OR 
            SRC_EXT STREQUAL ".h")
            set(MODULE_INFO_HAS_HEADERS ON PARENT_SCOPE)
        endif()

        if (SRC_EXT STREQUAL ".cpp" OR 
            SRC_EXT STREQUAL ".c")
            set(MODULE_INFO_HAS_SOURCES ON PARENT_SCOPE)
        endif()
    endforeach(src ${MODULE_SOURCES})
    
endmacro()