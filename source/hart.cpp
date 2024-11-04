#include "../include/hart.hpp"
#include "../include/elf_loader.hpp"

void Hart::save_in_memory(Segment& segment) {
    //how many bytes are needed for alignment
    uint64_t vaddr = segment.get_vaddr();
    uint64_t vp_alignment = (4096 - vaddr % 4096) % 4096;
    if(vp_alignment != 0) {
        vaddr += vp_alignment;
    }

    //reset the page offset
    uint64_t paddr = vaddr & ~(4096 - 1);

    memory.mem_store(paddr, segment.get_data(), segment.get_size());
}