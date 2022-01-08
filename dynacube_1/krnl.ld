ENTRY(entry)
OUTPUT_FORMAT("elf32-i386")
/* OUTPUT_FORMAT("binary") */
SECTIONS
{
    .text 0x100000 :
    {
    	code = .; _code = .;

    	*(.text)

    	*(.rodata*)
    	. = ALIGN(4096);
    }

    tend = .;
    
/* 0x106000 */

    .data :
    {
    	data = .; _data = .;

    	*(.data)
    	. = ALIGN(4096);
    }

    dend = .;

/* 0x108000 */
    bssstart = .;

    .bss :
    {
    	bss = .; _bss = .;

    	*(.bss)

     *(COMMON)
    	. = ALIGN(4096);
    }
    end = .; _end = .;
}
