#ifndef MM_H
#define MM_H
#include "../pmm/pmm.h"
#include "../multiboot.h"
void init_mm(multiboot_info_t *mbinfo, uint32_t kernelStart, uint32_t kernelEnd, uint32_t kernelSize);

#endif
