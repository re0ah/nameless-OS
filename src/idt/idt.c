#include "idt.h"

struct idt_entry idt[256] = {0};
const struct idtr
{
	uint16_t limit;			/*lenght of IDT in bytes - 1*/
	struct idt_entry* base; /*address where IDT starts*/
} __attribute((packed)) IDTR =
{
	sizeof(idt) - 1,
	&idt[0]
};

static const uint8_t OFFSET_PICM = 0x20;/*offset_picm - vector offset for PICM*/
static const uint8_t OFFSET_PICS = 0x28;/*offset_pics - vector offset for PICS*/
void irq_remap()
{
    outb(PICM,      ICW1_INIT | ICW1_TO_ICW4);/*start initialization*/
    /*io_waits calls need for works on older machine, to give the PIC some time to react to commands*/
    io_wait();
    outb(PICS,      ICW1_INIT | ICW1_TO_ICW4);/*start initialization*/
    io_wait();
    outb(PICM_DATA, OFFSET_PICM);             /*remap PICM to offset*/
    io_wait();
    outb(PICS_DATA, OFFSET_PICS);             /*remap PICS to offset*/
    io_wait();
    outb(PICM_DATA, 0x04);                    /*setup cascading*/
    io_wait();
    outb(PICS_DATA, 0x02);
    io_wait();
    outb(PICM_DATA, ICW4_8086);               /*8086/88 mode*/
    io_wait();
    outb(PICS_DATA, ICW4_8086);               /*8086/88 mode*/
}

void set_idt_handler(uint8_t index, void* handle)
{
/*at time of work this function may will do interrupt, and result will be undefined. Disable interruption and save flag register*/
	asm volatile("pushf\n\t");
	asm volatile("cli\n\t");
	idt[index].offset_1 = (size_t)handle & 0xFFFF;
	idt[index].offset_2 = (size_t)handle >> 16;
	idt[index].selector = 0x08; /*kernel code segment offset*/
	idt[index].reserved = 0;
	idt[index].type     = IDT_TYPE;
	/*load flag register. This also activate interruption*/
	asm volatile("popf\n\t");
}

__attribute__((interrupt)) void unus(void* unused)
{
	outb(PICM, PIC_EOI);/*write end of interrupt code to PICM*/
}

void init_idt()
{
	vga_print_string("Initialized The Interrupt Descriptor Table\n", 43);
	memset(&idt, 0, sizeof(idt));

	asm volatile("lidt (%0)" : : "a"(&IDTR)); /*load IDTR in IDTR, khm.*/
	irq_remap();
	
	set_idt_handler(ISR0,  unus);/*divide by zero*/
	set_idt_handler(ISR1,  unus);/*debug*/
	set_idt_handler(ISR2,  unus);/*non-mascable interrupt*/
	set_idt_handler(ISR3,  unus);/*breakpoint*/
	set_idt_handler(ISR4,  unus);/*overflow*/
	set_idt_handler(ISR5,  unus);/*bound range exceeded*/
	set_idt_handler(ISR6,  unus);/*invalid opcode*/
	set_idt_handler(ISR7,  unus);/*device not available*/
	set_idt_handler(ISR8,  unus);/*double fault*/
	set_idt_handler(ISR9,  unus);/*coprocessor segment overrun*/
	set_idt_handler(ISR10, unus);/*invalid TSS*/
	set_idt_handler(ISR11, unus);/*segment not present*/
	set_idt_handler(ISR12, unus);/*stack-segment fault*/
	set_idt_handler(ISR13, unus);/*general protection fault*/
	set_idt_handler(ISR14, unus);/*page fault*/
	set_idt_handler(ISR15, unus);/*reserved*/
	set_idt_handler(ISR16, unus);/*x87 floating-point exception*/
	set_idt_handler(ISR17, unus);/*alignment check*/
	set_idt_handler(ISR18, unus);/*machine check*/
	set_idt_handler(ISR19, unus);/*SIMD floating-point exception*/
	set_idt_handler(ISR20, unus);/*virtualization exception*/
	set_idt_handler(ISR21, unus);/*reserved*/
	set_idt_handler(ISR22, unus);/*reserved*/
	set_idt_handler(ISR23, unus);/*reserved*/
	set_idt_handler(ISR24, unus);/*reserved*/
	set_idt_handler(ISR25, unus);/*reserved*/
	set_idt_handler(ISR26, unus);/*reserved*/
	set_idt_handler(ISR27, unus);/*reserved*/
	set_idt_handler(ISR28, unus);/*reserved*/
	set_idt_handler(ISR29, unus);/*reserved*/
	set_idt_handler(ISR30, unus);/*security exception*/
	set_idt_handler(ISR31, unus);/*reserved*/

	init_pit();
	set_idt_handler(IRQ0,  pit_handler);     /*system timer*/
	set_idt_handler(IRQ1,  keyboard_handler);/*keyboard controller*/
	set_idt_handler(IRQ2,  unus);			 /*cascaded signals irqs 8-15*/
	set_idt_handler(IRQ3,  unus);			 /*com2 & com4*/
	set_idt_handler(IRQ4,  unus);			 /*com1 & com3*/
	set_idt_handler(IRQ5,  unus);			 /*lpt2, lpt3 | sound card*/
	set_idt_handler(IRQ6,  unus);			 /*floppy*/
	set_idt_handler(IRQ7,  unus);			 /*lpt1 | sound card*/
	set_idt_handler(IRQ8,  unus);			 /*real-time clock(RTC)*/
	set_idt_handler(IRQ9,  unus);			 /*advanced configuration and power interface (ACPI)*/
	set_idt_handler(IRQ10, unus);			 /*SCSI | NIC*/
	set_idt_handler(IRQ11, unus);			 /*SCSI | NIC*/
	set_idt_handler(IRQ12, unus);			 /*mouse*/
	set_idt_handler(IRQ13, unus);			 /*coprocessor | FPU | IPI*/
	set_idt_handler(IRQ14, unus);			 /*primary   ATA (cd drives, hard drives)*/
	set_idt_handler(IRQ15, unus);			 /*secondary ATA*/
}
