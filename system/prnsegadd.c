/* prnsegadd.c - prnsegadd */

#include <xinu.h>
#include <stdio.h>

void prnsegadd()
{
	kprintf("\ntext start - 0x%x\n", &text);
	kprintf("text end - 0x%x\n", &etext);
	kprintf("text length - %d\n", (uint32)&etext - (uint32)&text);
	kprintf("data start - 0x%x\n", &data);
	kprintf("data end - 0x%x\n", &edata);
	kprintf("data length - %d\n", (uint32)&edata - (uint32)&data);
	kprintf("bss start - 0x%x\n", &bss);
	kprintf("bss end - 0x%x\n", &ebss);
	kprintf("bss length - %d\n", (uint32)&ebss - (uint32)&bss);
	kprintf("XINU end - 0x%x\n", &end);
}
