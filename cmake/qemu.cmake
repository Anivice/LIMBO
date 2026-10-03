#
# @file qemu.cmake
# @brief This file provides CMake commands for boot and debug in QEMU
#
# @copyright
# Copyright 2025 Anivice Ives
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

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
            COMMAND ${QEMU_EXEC} -smp 1 -cpu pentium3,fpu
                -drive if=floppy,index=0,format=raw,file=${CMAKE_BINARY_DIR}/${FLOPPY_DRIVE_FILE}
                -drive if=ide,index=0,format=raw,file=${HARD_DISK_FILE}
                -m 32M -rtc base=localtime -boot a ${QEMU_ADDITIONAL_ARGS}
            COMMENT "Booting from floppy disk ${FLOPPY_DRIVE_FILE}..."
            DEPENDS ${HARD_DISK_FILE} ${CMAKE_BINARY_DIR}/${FLOPPY_DRIVE_FILE}
            USES_TERMINAL
            VERBATIM
    )

    add_custom_target(${NAME}_debug
            COMMAND ${QEMU_EXEC} -smp 1 -cpu pentium3,fpu
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
