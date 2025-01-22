#include <80x50vga.h>
#include <gdt.h>
#include <idt.h>
#include <multiboot2.h>

void hand()
{
    uint8_t scancode = inb(0x60);
    if (scancode)
    {
        vgaprint(scancode);
    }
}

void kernel_main() {
    gdt_init();
    idt_init();
    irq_install_handler(0, &hand);
}