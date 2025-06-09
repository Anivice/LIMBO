SECTIONS
{
  . = 0x00100000;
  .text : { *(.kernel_entry_point) *(.text*) *(*.get_pc_thunk.ax) }
  . = 0x00177E80;
  .data : { *(.rodata) *(.data)  *(.bss*) }
}
