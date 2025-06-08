find_program(NASM_EXECUTABLE nasm REQUIRED)
find_program(CAT_EXECUTABLE cat REQUIRED)
find_program(DD_EXECUTABLE dd REQUIRED)

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

function(concatenate_files)
    if (${ARGC} LESS 2)
        message(FATAL_ERROR "Incorrect use of this function. Expecting at least two arguments.")
    endif ()

    set(arg_list ${ARGN})
    list(GET arg_list 0 output_filename)
    list(REMOVE_AT arg_list 0)

    set(DD_COMMAND "${DD_EXECUTABLE} of=${CMAKE_CURRENT_BINARY_DIR}/${output_filename} bs=512 conv=sync,fdatasync iflag=fullblock")
    set(CAT_COMMAND "${CAT_EXECUTABLE}")
    foreach(arg IN LISTS arg_list)
        set(CAT_COMMAND "${CAT_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${arg}")
    endforeach()

    set(COMMAND "${CAT_COMMAND} | ${DD_COMMAND} 2> /dev/null > /dev/null")

    set(file_dep)
    set(comment)
    foreach(arg IN LISTS arg_list)
        LIST(APPEND file_dep "${CMAKE_CURRENT_BINARY_DIR}/${arg}")
        set(comment "${comment} ${arg}")
    endforeach()

    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${output_filename}
            COMMAND sh -c ${COMMAND}
            DEPENDS ${file_dep}
            COMMENT "Concatenating files${comment} to ${output_filename}"
            VERBATIM
    )

    add_custom_target(concatenate_file_${output_filename} ALL
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${output_filename}
            COMMENT "Concatenating files for target concatenate_file_${output_filename}"
    )
endfunction()

function(fill_space_with_empty_sectors FILE DESIRED)
    add_custom_target(${FILE}_RESIZE ALL
            COMMAND ${CMAKE_SOURCE_DIR}/scripts/fill_sec.sh ${CMAKE_CURRENT_BINARY_DIR}/${FILE} ${DESIRED}
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${FILE}
            COMMENT "Resizing file ${FILE}"
    )
endfunction()

function(form_1MB_kernel FILE OFILE DEP)
    add_custom_target(FormKernel ALL
            COMMAND ${CMAKE_SOURCE_DIR}/scripts/kcopy.sh ${CMAKE_CURRENT_BINARY_DIR}/${FILE} ${CMAKE_CURRENT_BINARY_DIR}/${OFILE}
            DEPENDS ${DEP}
            COMMENT "Dumping kernel code to 1MB image ${OFILE}"
    )
endfunction()
