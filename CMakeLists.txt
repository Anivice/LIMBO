cmake_minimum_required(VERSION 3.31.6)
project(LIMBO LANGUAGES ASM C)

include(cmake/compile_mbr.cmake)
add_asm_target(src/mbr/bootsec.asm)
add_asm_target(src/mbr/loader.asm)

concatenate_files(head.bin bootsec.bin loader.bin)
fill_space_with_empty_sectors(head.bin 128) # head is 128 sector in length, kernel code starts from [128](#129)

include(cmake/qemu.cmake)
add_emulation_target(boot head.bin dummy)
