#pragma once

#include <iostream>

#include "core/regfile.hpp"
#include "core/segment.hpp"
#include "core/inst.hpp"

#include "utils/constants.hpp"

#include "memory.hpp"
#include "stages/decoder.hpp"

//--------------------------------------------------------------------------
// Cells
//--------------------------------------------------------------------------
// Cell connecting fetch and decode stages
struct fd_cell {
    uint32_t inst;
    uint64_t addr;
};

// Cell connecting decode and execute stages
struct de_cell {
    Inst* inst;
};

// Cell connecting execute and memory stages
struct em_cell {

};

// Cell connecting memory and writeback stages
struct mw_cell {

};

//--------------------------------------------------------------------------
// Hart
//--------------------------------------------------------------------------
class Hart final {
private:
    uint64_t start_addr;

    Memory memory;
    Regfile regfile;
    Reg pc;
    Decoder  decoder;

// Pipeline stages
    void fetch ();
    fd_cell fd;
    void decode ();
    de_cell de;
    void execute ();
    em_cell em;
    void memory_access ();
    mw_cell mw;
    void write_back ();

// Auxiliary functions for inserting bubbles
    friend void set_nop_fd_cell (Hart& hart);
    friend void set_nop_de_cell (Hart& hart);

public:
// Interaction with memory
    void map_seg_to_VAS (Segment& segment);
    void set_start_addr (uint64_t vaddr) { start_addr = vaddr; }
    void load_from_memory (uint64_t vaddr, void* load_ptr, int load_size);
    void store_in_memory (uint64_t vaddr, uint64_t val, int store_size);
    void memory_dump () { memory.dump (); }
    
// Interaction with regfile
    inline void set_reg_val (uint8_t reg, uint64_t v) { regfile.set_reg_val (reg, v); }
    inline uint64_t get_reg_val (uint8_t reg) { return regfile.get_reg_val (reg); }
    inline void set_pc_val (uint64_t new_pc) { pc.set_val (new_pc); }
    inline uint64_t get_pc_val () { return pc.get_val (); }

// Main pipeline cycle
    void run_pipeline ();

    Hart () {
        // Setting stack pointer as the end of VAS
        regfile.set_reg_val (2, DEFAULT_MEM_SIZE);
    }

    void dump () {
        std::cout << "----------------------- Hart -------------------" << std::endl;
        std::cout << "pc = " << std::setfill ('0') << "0x" << std::setw(16) 
                  << std::hex << pc.get_val() << std::endl;
        std::cout << "----------------------- Regfile ----------------" << std::endl;
        regfile.dump();
        std::cout << "----------------------- Memory -----------------" << std::endl;
        memory.dump();
        std::cout << "----------------------- Stack ------------------" << std::endl;
        memory.dump_stack (get_reg_val(2));
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }
};