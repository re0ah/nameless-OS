#ifndef IDT_H
#define IDT_H
#include "../ports/ports.h"
#include "../pit/pit.h"
#include "../keyboard/keyboard.h"

struct idt_entry
{
	uint16_t offset_1;/*offset bits 0..15*/
    uint16_t selector;/*kernel code segment offset*/
    uint8_t  reserved;/*unused*/
    uint8_t  type;    /*type and attributes*/
                      /*0..3 bits - gates*/
                      /*4 bit     - storage segment*/
                      /*5..6 bits - gate call protection*/
                      /*7 bit     - used/unused interrupts*/
    uint16_t offset_2;/*offset bits 16..31*/
} __attribute__((packed));

/*CPU exceptions*/
static const uint8_t ISR0  = 0x00;/*divide by zero*/
static const uint8_t ISR1  = 0x01;/*debug*/
static const uint8_t ISR2  = 0x02;/*non-mascable interrupt*/
static const uint8_t ISR3  = 0x03;/*breakpoint*/
static const uint8_t ISR4  = 0x04;/*overflow*/
static const uint8_t ISR5  = 0x05;/*bound range exceeded*/
static const uint8_t ISR6  = 0x06;/*invalid opcode*/
static const uint8_t ISR7  = 0x07;/*device not available*/
static const uint8_t ISR8  = 0x08;/*double fault*/
static const uint8_t ISR9  = 0x09;/*coprocessor segment overrun*/
static const uint8_t ISR10 = 0x0a;/*invalid TSS*/
static const uint8_t ISR11 = 0x0b;/*segment not present*/
static const uint8_t ISR12 = 0x0c;/*stack-segment fault*/
static const uint8_t ISR13 = 0x0d;/*general protection fault*/
static const uint8_t ISR14 = 0x0e;/*page fault*/
static const uint8_t ISR15 = 0x0f;/*reserved*/
static const uint8_t ISR16 = 0x10;/*x87 floating-point exception*/
static const uint8_t ISR17 = 0x11;/*alignment check*/
static const uint8_t ISR18 = 0x12;/*machine check*/
static const uint8_t ISR19 = 0x13;/*SIMD floating-point exception*/
static const uint8_t ISR20 = 0x14;/*virtualization exception*/
static const uint8_t ISR21 = 0x15;/*reserved*/
static const uint8_t ISR22 = 0x16;/*reserved*/
static const uint8_t ISR23 = 0x17;/*reserved*/
static const uint8_t ISR24 = 0x18;/*reserved*/
static const uint8_t ISR25 = 0x19;/*reserved*/
static const uint8_t ISR26 = 0x1a;/*reserved*/
static const uint8_t ISR27 = 0x1b;/*reserved*/
static const uint8_t ISR28 = 0x1c;/*reserved*/
static const uint8_t ISR29 = 0x1d;/*reserved*/
static const uint8_t ISR30 = 0x1e;/*security exception*/
static const uint8_t ISR31 = 0x1f;/*reserved*/

/*master PIC IRQs*/
static const uint8_t IRQ0  = 0x20;/*system timer*/
static const uint8_t IRQ1  = 0x21;/*keyboard controller*/
static const uint8_t IRQ2  = 0x22;/*cascaded signals irqs 8-15*/
static const uint8_t IRQ3  = 0x23;/*com2 & com4*/
static const uint8_t IRQ4  = 0x24;/*com1 & com3*/
static const uint8_t IRQ5  = 0x25;/*lpt2, lpt3 | sound card*/
static const uint8_t IRQ6  = 0x26;/*floppy*/
static const uint8_t IRQ7  = 0x27;/*lpt1 | sound card*/
/*slave PIC IRQs*/
static const uint8_t IRQ8  = 0x28;/*real-time clock(RTC)*/
static const uint8_t IRQ9  = 0x29;/*advanced configuration and power interface (ACPI)*/
static const uint8_t IRQ10 = 0x2a;/*SCSI | NIC*/
static const uint8_t IRQ11 = 0x2b;/*SCSI | NIC*/
static const uint8_t IRQ12 = 0x2c;/*mouse*/
static const uint8_t IRQ13 = 0x2d;/*coprocessor | FPU | IPI*/
static const uint8_t IRQ14 = 0x2e;/*primary   ATA (cd drives, hard drives)*/
static const uint8_t IRQ15 = 0x2f;/*secondary ATA*/

static const uint8_t IDT_TYPE     = 0x8E;/*
                                *gate type(0..3 bits)            = 0x0E, 32-bits interrupt gate
                                *storage segment(4 bit)          = 0x00, for interrupt/trap gates
                                *gate call protection(5..6 bits) = 0x00, ring
                                *used/unused interrupts(7 bit)   = 0x01, used
                                         */
static const uint8_t PICM         = 0x20;/*IO base address for master PIC*/
static const uint8_t PICS         = 0xA0;/*IO base address for slave  PIC*/
static const uint8_t PICM_DATA    = 0x21;/**/
static const uint8_t PICS_DATA    = 0xA1;/**/
static const uint8_t PIC_EOI      = 0x20;/*End of interrupt command code*/
/*ICW - command initialization*/
static const uint8_t ICW1_TO_ICW4 = 0x01;/*switch ICW1 to ICW4*/
static const uint8_t ICW1_INIT    = 0x10;/*Initialization ICW1*/
static const uint8_t ICW4_8086    = 0x01;/*8086/88 (MCS-80/85) mode*/

extern const struct idtr IDTR;

void irq_remap();
void set_idt_handler(uint8_t index, void* handle);
void init_idt();

#endif
