#include <80x50vga.h>
#include <gdt.h>
#include <idt.h>

void kernel_main(void) {
    vgaprint("NET-DOS VGA 80x25 driver testing...\n");
    gdt_init();
    vgaprint("GDT initialized\n");
    idt_init();
    vgaprint("IDT initialized\nDeviding by 0...\n");
    vgaprint(1/0);
}