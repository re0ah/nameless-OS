[GLOBAL loader]

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x00000001

CHECKSUM     equ -(MAGIC_NUMBER + FLAGS)

KERNEL_STACK_SIZE equ 4096

section .text
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM


	loader:
		mov esp, kernel_stack + KERNEL_STACK_SIZE

		[EXTERN kernel]
		push edx
		push ebx
		call kernel

	.loop:
		jmp .loop

section .bss
align 4
	kernel_stack:
		resb KERNEL_STACK_SIZE
