ENTRY(main)

SECTIONS
{
  /* Fixed image slots: 256 KiB code, 312 KiB data, then the symbol map. */
  . = 0x00100000;
  .text : {
    KEEP(*(.kernel_entry_point))
    *(.text*)
    *(*.get_pc_thunk.ax)
  }

  . = 0x00140000;
  .data : {
    *(.rodata .rodata.*)
    *(.data .data.*)
    *(.bss .bss.*)
    *(COMMON)
  }

  /DISCARD/ : { *(.note.gnu.build-id) }

  ASSERT(main == 0x00100000, "Kernel entry must be at 0x00100000")
  ASSERT(SIZEOF(.text) <= 0x40000, "Kernel code exceeds its image slot")
  ASSERT(SIZEOF(.data) <= 0x4E000, "Kernel data exceeds its image slot")
}