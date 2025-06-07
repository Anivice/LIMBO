find_program(NASM_EXECUTABLE nasm REQUIRED)
message(STATUS "Found nasm: ${NASM_EXECUTABLE}")

function(split_on_dot OUT_VAR IN_STRING)
    set(options KEEP_EMPTY)
    cmake_parse_arguments(SPLIT_DOT "" "${options}" "" ${ARGN})
    string(REPLACE "." ";" _tmp_list "${IN_STRING}")
    if (NOT SPLIT_DOT_KEEP_EMPTY)
        list(FILTER _tmp_list EXCLUDE REGEX "^$")
    endif()
    set(${OUT_VAR} "${_tmp_list}" PARENT_SCOPE)
endfunction()

function(remove_path_prefix IN_VAR OUT_VAR)
    set(_full "${${IN_VAR}}")
    string(REGEX REPLACE ".*/" "" _candidate "${_full}")
    if (NOT "${_candidate}" STREQUAL "${_full}")
        set(${OUT_VAR} "${_candidate}" PARENT_SCOPE)
        return()
    endif()
    string(FIND "${_full}" "/" _pos REVERSE)
    if (_pos EQUAL -1)
        set(${OUT_VAR} "${_full}" PARENT_SCOPE)
    else()
        math(EXPR _start "${_pos} + 1")
        string(SUBSTRING "${_full}" ${_start} -1 _basename)
        set(${OUT_VAR} "${_basename}" PARENT_SCOPE)
    endif()
endfunction()

function(add_asm_target FILE)
    remove_path_prefix(FILE BASENAME)
    split_on_dot(BASENAME_FILE_VEC ${BASENAME})
    list(GET BASENAME_FILE_VEC 0 FILEBASE)

    set(INFILE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})
    set(OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/${FILEBASE}.bin)

    # Generate binary file from assembly source
    add_custom_command(
            OUTPUT ${OUTFILE}
            COMMAND ${NASM_EXECUTABLE} -O0 -X gnu -f bin ${INFILE} -o ${OUTFILE}
            DEPENDS ${INFILE}
            COMMENT "Assembling ${INFILE} with NASM"
    )

    # Create a target to manage dependencies and build
    add_custom_target(${FILEBASE}_MBR_BINARY ALL
            DEPENDS ${OUTFILE}
            COMMENT "Building binary target ${OUTFILE}"
    )
endfunction()
