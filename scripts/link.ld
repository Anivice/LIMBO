ENTRY(main)

SECTIONS
{
  . = 0x00100000;
  .text : {
    KEEP(*(.kernel_entry_point))
    *(.text*)
    *(*.get_pc_thunk.ax)
  }

  . = 0x00178000;
  .data : {
    *(.rodata .rodata.*)
    *(.data .data.*)
    *(.bss .bss.*)
    *(COMMON)
  }

  /DISCARD/ : { *(.note.gnu.build-id) }

  ASSERT(main == 0x00100000, "Kernel entry must be at 0x00100000")
  ASSERT(SIZEOF(.text) <= 0x78000, "Kernel code exceeds its image slot")
  ASSERT(SIZEOF(.data) <= 0x16000, "Kernel data exceeds its image slot")
}