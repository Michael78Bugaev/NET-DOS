# Компиляторы и флаги
CC = gcc
ASM = nasm
LD = ld

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -I ./include -nostartfiles -nodefaultlibs -Wall -Wextra -c
ASMFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# Папки для исходников и сборки
SRC_DIR = .
BUILD_DIR = build
ASM_BUILD_DIR = $(BUILD_DIR)/asm
C_BUILD_DIR = $(BUILD_DIR)/c

# Поиск всех .c и .asm файлов (включая поддиректории)
SRC_C = $(shell find $(SRC_DIR) -type f -name '*.c')
SRC_ASM = $(shell find $(SRC_DIR) -type f -name '*.asm')

# Генерация списка объектных файлов
OBJ_C = $(patsubst $(SRC_DIR)/%.c, $(C_BUILD_DIR)/%.o, $(SRC_C))
OBJ_ASM = $(patsubst $(SRC_DIR)/%.asm, $(ASM_BUILD_DIR)/%.o, $(SRC_ASM))

# Итоговый образ системы
OS_IMAGE = net-dos

# Цель по умолчанию
all: $(OS_IMAGE)

# Сборка итогового образа
$(OS_IMAGE): $(OBJ_C) $(OBJ_ASM)
	@$(LD) $(LDFLAGS) -o $@ $^
	@cp $(OS_IMAGE) iso_dir/boot

	@grub-mkrescue -o netdos.iso iso_dir
	@qemu-system-i386 -cdrom netdos.iso

# Компиляция .c файлов
$(C_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "CC	" $^
	@$(CC) $(CFLAGS) -o $@ $<

# Компиляция .asm файлов
$(ASM_BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	@echo "AS	" $^
	$(ASM) $(ASMFLAGS) -o $@ $<

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(OS_IMAGE)

.PHONY: all