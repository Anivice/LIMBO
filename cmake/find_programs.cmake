function(limbo_gnu_identifier EXEC VERSION ACTUAL_VERSION)
    # Get info
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/scripts/get_identifier.sh "${EXEC}"
            OUTPUT_VARIABLE VERSION_IDENTIFIER
            RESULT_VARIABLE GNU_VERSION_EXIT_STATUS)

    # check command status
    if (NOT "${GNU_VERSION_EXIT_STATUS}" EQUAL 0)
        message(FATAL_ERROR "Cannot obtain identifier and version for ${EXEC}, or ${EXEC} has no GNU identifier")
    endif ()

    # format
    string(STRIP ${VERSION_IDENTIFIER} VERSION_IDENTIFIER)

    # check actual content
    if (${VERSION_IDENTIFIER} VERSION_LESS "${VERSION}")
        message(FATAL_ERROR "${EXEC} self-identified as ${VERSION_IDENTIFIER}, but ${VERSION} or above required")
    else ()
        set(${ACTUAL_VERSION} ${VERSION_IDENTIFIER} PARENT_SCOPE)
    endif ()
endfunction()
