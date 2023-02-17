macro(glob_file)
    cmake_parse_arguments(
            GLOB
            ""
            "OUTPUT"
            "INPUT_FILES"
            ${ARGN}
    )

    file(
            GLOB_RECURSE
            ${GLOB_OUTPUT}
            ${GLOB_INPUT_FILES}
    )

    # File order can change the final binary build (see https://blog.conan.io/2019/09/02/Deterministic-builds-with-C-C++.html),
    # so we make sure that compilation unit are explicitly sorted
    list(SORT ${GLOB_OUTPUT} ORDER DESCENDING)

    # When LTO is activated, GCC generate random symbol names. Whe make theses symboles not so random
    # by choosing the seed for each files using their checksum. It's good for reproductible build
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        foreach(_file IN LISTS ${GLOB_OUTPUT})
            file(SHA1 ${_file} checksum)
            string(SUBSTRING ${checksum} 0 8 checksum)
            set_property(SOURCE ${_file} APPEND_STRING PROPERTY COMPILE_FLAGS "-frandom-seed=0x${checksum}")
        endforeach()
    endif()
endmacro()