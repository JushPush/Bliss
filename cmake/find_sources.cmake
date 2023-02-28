# Utility macro to find files in directory and store into the given parameter

macro(bliss_find_sources sources directory)
	file(GLOB_RECURSE sources ${BLISS_FILE_TYPES})
	list(FILTER sources INCLUDE REGEX ${directory})
endmacro()