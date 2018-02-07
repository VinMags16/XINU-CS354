/* prnsegadd.c - prnsegadd */

#include <xinu.h>
#include <stdio.h>

void prnsegadd()
{
	kprintf("\nStart of Text at 0x%x, end of Text at 0x%x\n", &text, &etext);
	kprintf("Start of Data at 0x%x, end of Data at 0x%x\n", &data, &edata);
	kprintf("Start of Bss at 0x%x, end of Bss at 0x%x\n", &bss, &ebss);
	kprintf("XINU end at 0x%x\n", &end);
	kprintf("Text Length : %d bytes\n", (uint32)&etext - (uint32)&text);
	kprintf("Data Length : %d bytes\n", (uint32)&edata - (uint32)&data);
	kprintf("Bss Length : %d bytes\n", (uint32)&ebss - (uint32)&bss);

}
