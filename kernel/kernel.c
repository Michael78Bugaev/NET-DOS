#include <80x50vga.h>
#include <gdt.h>

void kernel_main(void) {
    vgaprint("NET-DOS VGA 80x25 driver testing...\n");
    gdt_init();
    vgaprint("GDT initialized");
}