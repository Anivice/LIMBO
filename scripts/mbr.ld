OUTPUT_FORMAT("binary")
ENTRY(start)
SECTIONS
{
  /* Place code at 0x7C00 */
  . = 0x00007C00;
  .text : { *(.text) }

  /* Stop at 0x7E00 (= 0x7C00 + 512) */
  . = 0x00007E00;
  /DISCARD/ : { *(.comment) *(.note.*) }
}
