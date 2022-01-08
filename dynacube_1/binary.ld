ENTRY(main)
OUTPUT_FORMAT("binary")
SECTIONS
{
    .text 0x000000 :
    {
    	code = .; _code = .;

    	*(.text)

    	*(.rodata*)
    	. = ALIGN(4096);
    }
}
