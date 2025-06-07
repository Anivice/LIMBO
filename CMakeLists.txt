cmake_minimum_required(VERSION 3.31.6)
project(LIMBO LANGUAGES ASM C)

include(cmake/compile_mbr.cmake)
add_asm_target(src/mbr/bootsec.asm)
add_asm_target(src/mbr/loader.asm)

concatenate_files(limbo.bin bootsec.bin loader.bin)

include(cmake/qemu.cmake)
add_emulation_target(boot limbo.bin dummy)
