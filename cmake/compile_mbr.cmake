include(${CMAKE_SOURCE_DIR}/cmake/find_programs.cmake)

find_program(AS_EXECUTABLE as REQUIRED)
find_program(CC_EXECUTABLE cc REQUIRED)
find_program(LD_EXECUTABLE ld REQUIRED)

limbo_gnu_identifier(${AS_EXECUTABLE} 2.44 AS_VERSION)
limbo_gnu_identifier(${CC_EXECUTABLE} 15.1 CC_VERSION)
limbo_gnu_identifier(${LD_EXECUTABLE} 2.44 LD_VERSION)

message(STATUS "Found as: ${AS_EXECUTABLE} ${AS_VERSION}")
message(STATUS "Found cc: ${CC_EXECUTABLE} ${CC_VERSION}")
message(STATUS "Found ld: ${LD_EXECUTABLE} ${LD_VERSION}")

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

function(add_mbr_target FILE)
    remove_path_prefix(FILE BASENAME)
    split_on_dot(BASENAME_FILE_VEC ${BASENAME})
    list(GET BASENAME_FILE_VEC 0 FILEBASE)
    add_custom_target(LIMBO_SYSTEM_MBR_ASSEMBLE
            COMMAND ${AS_EXECUTABLE} --32 ${CMAKE_CURRENT_SOURCE_DIR}/${FILE} -o ${CMAKE_CURRENT_BINARY_DIR}/${FILEBASE}.o
            COMMENT "Assembling MBR boot sector file ${BASENAME}"
            BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/${FILEBASE}.o
    )

    add_custom_target(LIMBO_SYSTEM_MBR_LINK
            COMMAND ${LD_EXECUTABLE} -m elf_i386 -T ${CMAKE_SOURCE_DIR}/scripts/mbr.ld -Ttext=0x7C00 --oformat binary ${CMAKE_BINARY_DIR}/${FILEBASE}.o -o ${CMAKE_CURRENT_BINARY_DIR}/${FILEBASE}.bin
            COMMENT "Linking MBR boot sector file ${FILEBASE}.o to ${FILEBASE}.bin"
            BYPRODUCTS ${CMAKE_BINARY_DIR}/${FILEBASE}.bin
            DEPENDS LIMBO_SYSTEM_MBR_ASSEMBLE
    )

    add_custom_target(LIMBO_MBR ALL DEPENDS LIMBO_SYSTEM_MBR_LINK)
endfunction()
