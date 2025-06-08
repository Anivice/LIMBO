SECTIONS
{
  /* 1MiB = 0x100000 */
  . = 0x00100000;
  .text : { *(.text*) *(__x86.get_pc_thunk.ax) }

  /* 1MiB + 640KiB = 0x100000 + 0xA0000 = 0x1A0000 */
  . = 0x001A0000;
  .data : { *(.rodata) *(.data) *(.bss COMMON) }
}
