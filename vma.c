#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void paging_info(uint64_t virtual_memory) {
    // Define masks for each paging level
    uint64_t mask_pml4 = 0x1FFULL << 39; // Bits 39-47
    uint64_t mask_pdp  = 0x1FFULL << 30; // Bits 30-38
    uint64_t mask_pd   = 0x1FFULL << 21; // Bits 21-29
    uint64_t mask_pt   = 0x1FFULL << 12; // Bits 12-20
    uint64_t mask_offset = 0xFFF;        // Bits 0-11

    // Extract indices using bitwise operations
    uint64_t index_pml4 = (virtual_memory & mask_pml4) >> 39;
    uint64_t index_pdp  = (virtual_memory & mask_pdp) >> 30;
    uint64_t index_pd   = (virtual_memory & mask_pd) >> 21;
    uint64_t index_pt   = (virtual_memory & mask_pt) >> 12;
    uint64_t page_offset = virtual_memory & mask_offset;

    // Print results
    printf("Virtual Address: %p\n", virtual_memory);
    printf("Index into PML4: %lu\n", index_pml4);
    printf("Index into PDP:  %lu\n", index_pdp);
    printf("Index into PD:   %lu\n", index_pd);
    printf("Index into PT:   %lu\n", index_pt);
    printf("Page Offset:     %lu\n", page_offset);
}

int main() {
    // malloc 1 int, or 4 bytes
    void *memory = malloc(1*sizeof(int));
    if (NULL == memory) {
        printf("Malloc failed");
        return 1;
    }

    // Unsigned 64bit int
    uint64_t virtual_memory = (uint64_t)memory;
    paging_info(virtual_memory);
    free(memory);
    return 0;
}