/***********************************************************************/
/*                                                                     */
/*  ROM.ld:  Linker Script File                                        */
/*                                                                     */
/***********************************************************************/
ENTRY(_boot)
STACK_SIZE = 0x400;

/* Memory Definitions */
/* lpc2129 mt */
MEMORY
{
  ROM (rx) : ORIGIN = 0x00000000, LENGTH = 8k
  RAM (rw) : ORIGIN = 0x40000000, LENGTH = 2k
}

/* Section Definitions */
SECTIONS
{
  /* first section is .text which is used for code */
  .text :
  {
    *crt0.o (.text)            /* Startup code */
    *(.text)                   /* remaining code */
    *(.rodata)                 /* read-only data (constants) */
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
  } > ROM

  . = ALIGN(4);
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > ROM
  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    KEEP(*(SORT(.ctors.*)))
    KEEP(*(.ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > ROM
  /* Destructors aren't usefull in an embedded system.
  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > ROM
  */
    . = ALIGN(4);
  
  
  _etext = . ;
  PROVIDE (etext = .);

  /* .data section which is used for initialized data */
  .data : AT (_etext)
  {
    _data = .;
    *(.data)
	SORT(CONSTRUCTORS) /* mt 4/2005 */
  } > RAM
 
  . = ALIGN(4);
  _edata = . ;
  PROVIDE (edata = .);

  /* .bss section which is used for uninitialized data */
  .bss (NOLOAD) :
  {
    __bss_start = . ;
    __bss_start__ = . ;
    *(.bss)
    *(COMMON)
    . = ALIGN(4);
  } > RAM

  . = ALIGN(4);
  __bss_end__ = . ;
  PROVIDE (__bss_end = .);

 /* .stack ALIGN(256) : */
  .stack :
  {
    . = ALIGN(256);
    . += STACK_SIZE;
    PROVIDE (_stack = .);
  } > RAM

  _end = . ;
  PROVIDE (end = .);

  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
