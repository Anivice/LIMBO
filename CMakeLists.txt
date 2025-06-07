cmake_minimum_required(VERSION 3.31.6)
project(LIMBO LANGUAGES ASM C)

include(cmake/compile_mbr.cmake)
add_asm_target(src/mbr/bootsec.asm)
add_asm_target(src/mbr/loader.asm)

include(cmake/qemu.cmake)
add_emulation_target(boot bootsec.bin dummy)
