cmake_minimum_required(VERSION 3.31.6)
project(LIMBO LANGUAGES ASM C)

include(cmake/compile_mbr.cmake)
add_asm_target(src/mbr/bootsec.asm)
add_asm_target(src/mbr/loader.asm)

concatenate_files(head.bin bootsec.bin loader.bin)
fill_space_with_empty_sectors(head.bin head.resized.bin 18) # head is 18 sector in length

set(CMAKE_C_STANDARD 23)
add_compile_options(-ffreestanding -nostdlib -nodefaultlibs -static -nostartfiles -m32 -fno-PIE -fno-PIC -no-pie -Wl,-no-pie)
add_link_options(-ffreestanding -nostdlib -nodefaultlibs -static -nostartfiles -m32 -T ${CMAKE_SOURCE_DIR}/scripts/link.ld
        -fno-PIE -fno-PIC -no-pie -Wl,-no-pie)

include_directories(src/include)
add_library(limbo SHARED src/entry.c
        src/drivers/gpu.c src/include/gpu.h
        src/drivers/io.c src/include/io.h
        src/basic/printk.c src/include/printk.h
        src/drivers/ide.c src/include/ide.h
        src/basic/string.c src/include/string.h
)

execute_process(COMMAND sh -c "git log | head -n 1 | awk '{ print $NF }' | head -c 8"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GITVERSION)
add_compile_definitions(LIMBO_VERSION="0.0.1-${GITVERSION}")

form_1MB_kernel(liblimbo.so limbo.bin limbo)
concatenate_files(boot.bin head.resized.bin limbo.bin)
add_dependencies(concatenate_file_boot.bin head.bin_RESIZE) # file merge needs head to be resized first
fill_space_with_empty_sectors(boot.bin boot.img 2880) # 1.44MB floppy disk

include(cmake/qemu.cmake)
add_emulation_target(boot boot.img dummy)
add_dependencies(boot FormKernel)
add_dependencies(boot_debug FormKernel)
