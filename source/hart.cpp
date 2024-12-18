#include "stages/executor.hpp"
#include "hart.hpp"
#include "memory/mmu.hpp"

Hart::Hart() {
    // Setting stack pointer as the end of VAS
    regfile.set_reg_val (2, DEFAULT_MEM_SIZE);

    uint64_t root_page_addr = memory.get_clean_pages();
    prepare_page_table(*this, root_page_addr);
}

//--------------------------------------------------------------------------
// Interaction with memory
//--------------------------------------------------------------------------
void Hart::map_seg_to_VAS (Segment& segment) {
    //how many bytes are needed for alignment
    uint64_t vaddr = segment.get_vaddr();
    uint64_t vp_alignment = (VPAGE_SIZE - vaddr % VPAGE_SIZE) % VPAGE_SIZE;
    if (vp_alignment != 0) {
        uint64_t vaddr_without_mask = vaddr & VPAGE_OFFSET_MASK;
        //check if the page is readable or writable
        if (segment.get_flag() & (PF_W | PF_R)) {
            return;
        }

        memory.mem_store (vaddr - start_addr, segment.get_data(), vp_alignment);
        //memory.mem_store (from_vaddr_to_paddr(*this, vaddr), segment.get_data(), vp_alignment);
    }

    //copy the remaining pages
    for (uint64_t vpage_offset = 0; vpage_offset < segment.get_size() - vp_alignment; vpage_offset += VPAGE_SIZE) {
        //uint64_t paddr = from_vaddr_to_paddr(*this, vaddr + vp_alignment + vpage_offset);
        uint64_t paddr = vaddr + vp_alignment + vpage_offset - start_addr;

        //determine the size for the record
        size_t store_size = VPAGE_SIZE;
        if ((segment.get_size() - vp_alignment - vpage_offset) < VPAGE_SIZE)
            store_size = segment.get_size() - vp_alignment - vpage_offset;
            
        memory.mem_store (paddr, (char*)segment.get_data() + vp_alignment + vpage_offset, store_size);
    }
}

void Hart::load_from_memory (uint64_t vaddr, void* load_ptr, int load_size) {
    assert ((load_size == BYTE_SIZE) || (load_size == HWORD_SIZE) ||
            (load_size == WORD_SIZE) || (load_size == DWORD_SIZE) &&
            "incorrect load size (only 1, 2, 4, 8 b)");
    assert (((vaddr % load_size) == 0) && "incorrect alignment");
    
    memory.mem_load (from_vaddr_to_paddr(*this, vaddr), load_ptr, load_size);
}

void Hart::store_in_memory (uint64_t vaddr, uint64_t val, int store_size) {
    assert ((store_size == BYTE_SIZE) || (store_size == HWORD_SIZE) ||
            (store_size == WORD_SIZE) || (store_size == DWORD_SIZE) &&
            "incorrect load size (only 1, 2, 4, 8 b)");
    assert (((vaddr % store_size) == 0) && "incorrect alignment");
    
    memory.mem_store (from_vaddr_to_paddr(*this, vaddr), &val, store_size);
}

//--------------------------------------------------------------------------
// Pipeline stages
//--------------------------------------------------------------------------
void Hart::fetch () {
    uint64_t cur_pc_val = pc.get_val();
    uint32_t cur_inst;

    load_from_memory (pc.get_val(), &cur_inst, WORD_SIZE);

    fd.inst = cur_inst;
    fd.addr = pc.get_val();

    pc.set_val (cur_pc_val + WORD_SIZE);
}

void Hart::decode () {
    uint32_t cur_fd_inst = fd.inst;

    Inst* cur_de_inst = decoder.decode_inst (cur_fd_inst);
    cur_de_inst->addr = fd.addr;

    de.inst = cur_de_inst;
}

void Hart::execute () {
    Inst* cur_de_inst = de.inst;

    cur_de_inst->execute_func (cur_de_inst, *this);

    cur_de_inst->~Inst();
}

void Hart::memory_access () {

}

void Hart::write_back () {

}

//--------------------------------------------------------------------------
// Main pipeline cycle
//--------------------------------------------------------------------------
void Hart::run_pipeline () {
    while (true) {
        set_reg_val (0, 0);

        dump();

        fetch();
        decode();
        execute();
    }
}