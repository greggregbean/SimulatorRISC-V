#include "hart.hpp"
#include "elf_loader.hpp"

void Hart::save_in_memory (Segment& segment) {
    //how many bytes are needed for alignment
    uint64_t vaddr = segment.get_vaddr();
    uint64_t vp_alignment = (VPAGE_SIZE - vaddr % VPAGE_SIZE) % VPAGE_SIZE;
    if (vp_alignment != 0) {
        //check if the page is readable or writable
        if (segment.get_flag() & (PF_W || PF_R)) {
            return;
        }

        memory.mem_store (vaddr - BASE_ADDRESS, segment.get_data(), vp_alignment);
    }

    //copy the remaining pages
    for (uint64_t vpage_offset = 0; vpage_offset < segment.get_size() - vp_alignment; vpage_offset += VPAGE_SIZE) {
        uint64_t paddr = vaddr + vp_alignment + vpage_offset - BASE_ADDRESS;

        //determine the size for the record
        size_t store_size = VPAGE_SIZE;
        if ((segment.get_size() - vp_alignment - vpage_offset) < VPAGE_SIZE)
            store_size = segment.get_size() - vp_alignment - vpage_offset;

        void* add = (char*)segment.get_data() + vp_alignment + vpage_offset;
        memory.mem_store (paddr, (char*)segment.get_data() + vp_alignment + vpage_offset, store_size);
    }
}

void Hart::load_from_memory(uint64_t vaddr, void* load_ptr, int load_size) {
    assert ((load_size == BYTE_SIZE) || (load_size == HWORD_SIZE) ||
            (load_size == WORD_SIZE) || (load_size == DWORD_SIZE) &&
            "incorrect load size(only 8, 16, 32, 64 b)");
    assert (vaddr & (load_size - 1) == 0 && "incorrect alignment");
    
    memory.mem_load (vaddr - BASE_ADDRESS, load_ptr, load_size);
}

void Hart::fetch () {

}

void Hart::decode () {

}

void Hart::run_pipeline () {
    while (true) {
        fetch();
        decode();
        execute();
    }
}