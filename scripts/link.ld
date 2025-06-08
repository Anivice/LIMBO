SECTIONS
{
  . = 0x00100000;
  .text : { *(.text*) *(__x86.get_pc_thunk.ax) }
  . = 0x00177E64;
  .data : { *(.rodata) *(.data) *(.bss COMMON) }
}
