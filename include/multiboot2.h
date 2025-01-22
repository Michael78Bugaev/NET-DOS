#ifndef MULTIBOOT2_H
#define MULTIBOOT2_H

#include <stdint.h>

// Структура заголовка Multiboot2
typedef struct {
    uint32_t magic;         // 0x1BADB002
    uint32_t architecture;  // 0 (i386) или 1 (x86-64)
    uint32_t header_length; // Длина заголовка Multiboot2
    uint32_t checksum;      // Сумма контрольных сумм заголовка Multiboot2

    uint32_t mem_lower;     // Низкая часть доступной памяти
    uint32_t mem_upper;     // Высокая часть доступной памяти

    uint32_t load_addr;     // Адрес загрузки ядра
    uint32_t load_end_addr; // Адрес окончания загрузки ядра
    uint32_t bss_end_addr;  // Адрес окончания сегмента BSS

    uint32_t entry_addr;    // Адрес точки входа ядра

    uint32_t mod_count;     // Количество модулей
    uint32_t mod_addr;      // Адрес начала модулей

    uint32_t elf_symbols;   // Адрес таблицы символов ELF
    uint32_t elf_symbols_size; // Размер таблицы символов ELF

    uint32_t mmap_length;   // Длина карты памяти
    uint32_t mmap_addr;     // Адрес карты памяти

    uint32_t drive_info;    // Информация о дисковом устройстве
    uint32_t config_table;  // Адрес таблицы конфигурации

    uint32_t boot_loader_name; // Адрес строки с именем загрузчика
    uint32_t apm_table;     // Адрес таблицы APM

    uint32_t vbe_control_info; // Адрес информации о контроллере VBE
    uint32_t vbe_mode_info;   // Адрес информации о режиме VBE
    uint16_t vbe_mode;       // Режим VBE
    uint16_t vbe_interface_seg; // Сегмент интерфейса VBE
    uint16_t vbe_interface_off; // Смещение интерфейса VBE
    uint16_t vbe_interface_len; // Длина интерфейса VBE

    uint64_t framebuffer_addr; // Адрес видеобуфера
    uint32_t framebuffer_pitch; // Ширина видеобуфера
    uint32_t framebuffer_width; // Ширина видеоэкрана
    uint32_t framebuffer_height; // Высота видеоэкрана
    uint32_t framebuffer_bpp;    // Глубина цвета видеоэкрана
    uint32_t framebuffer_type;   // Тип видеобуфера

    uint32_t acpi_old_address; // Старый адрес таблицы ACPI
    uint32_t acpi_new_address; // Новый адрес таблицы ACPI

    uint32_t smbios_address; // Адрес таблицы SMBIOS

    uint32_t reserved;       // Reserved
} multiboot2_info_t;

#endif // MULTIBOOT2_H