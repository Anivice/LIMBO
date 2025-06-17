find_program(QEMU_EXEC qemu-system-i386 REQUIRED)

add_custom_target(DUMMY ALL
        COMMAND touch ${CMAKE_BINARY_DIR}/dummy
        BYPRODUCTS ${CMAKE_BINARY_DIR}/dummy
        COMMENT "Creating an empty file ${CMAKE_BINARY_DIR}/dummy"
)

function(default_args MARCO DEFAULT_VALUE)
    if (NOT DEFINED ${MARCO})
        set(${MARCO} ${DEFAULT_VALUE} PARENT_SCOPE)
    else ()
        message(STATUS "${MARCO} overridden as `${${MARCO}}`")
        string(REPLACE " " ";" ${MARCO} "${${MARCO}}")
        set(${MARCO} ${${MARCO}} PARENT_SCOPE)
    endif ()
endfunction()

default_args(QEMU_ADDITIONAL_ARGS "")

function(add_emulation_target NAME FLOPPY_DRIVE_FILE)
    set(HARD_DISK_FILE)
    list(LENGTH ARGN ARGC)
    if (${ARGC} EQUAL 1)
        list(GET ARGN 0 HARD_DISK_FILE)
        set(HARD_DISK_FILE ${CMAKE_BINARY_DIR}/${HARD_DISK_FILE})
    else ()
        set(HARD_DISK_FILE /dev/null)
    endif ()

    add_custom_target(${NAME}
            COMMAND ${QEMU_EXEC} -smp 1 -cpu 486,fpu
                -drive if=floppy,index=0,format=raw,file=${CMAKE_BINARY_DIR}/${FLOPPY_DRIVE_FILE}
                -drive if=ide,index=0,format=raw,file=${HARD_DISK_FILE}
                -m 32M -rtc base=localtime -boot a ${QEMU_ADDITIONAL_ARGS}
            COMMENT "Booting from floppy disk ${FLOPPY_DRIVE_FILE}..."
            DEPENDS ${HARD_DISK_FILE} ${CMAKE_BINARY_DIR}/${FLOPPY_DRIVE_FILE}
            USES_TERMINAL
            VERBATIM
    )

    add_custom_target(${NAME}_debug
            COMMAND ${QEMU_EXEC} -smp 1 -cpu 486,fpu
                -drive if=floppy,index=0,format=raw,file=${CMAKE_BINARY_DIR}/${FLOPPY_DRIVE_FILE}
                -drive if=ide,index=0,format=raw,file=${HARD_DISK_FILE}
                -m 32M -rtc base=localtime -boot a -gdb tcp::1234 -S ${QEMU_ADDITIONAL_ARGS}
                # -d int,in_asm,cpu,exec,in_asm
                # -D qemu_${NAME}_debug.log
            COMMENT "Booting from floppy disk ${FLOPPY_DRIVE_FILE}..."
            DEPENDS ${HARD_DISK_FILE} ${CMAKE_BINARY_DIR}/${FLOPPY_DRIVE_FILE}
            USES_TERMINAL
            VERBATIM
    )
endfunction()
