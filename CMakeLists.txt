cmake_minimum_required(VERSION 3.31.6)
project(LIMBO LANGUAGES ASM C)

include(cmake/compile_mbr.cmake)
add_mbr_target(test/as_compiling_test.asm)

include(cmake/qemu.cmake)
add_emulation_target(boot as_compiling_test.bin dummy)
