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
class fd_cell {
private:
    uint32_t inst;

public:
    uint32_t get_inst () { return inst; }
    void set_inst (uint32_t i) { inst = i; }
};

// Cell connecting decode and execute stages
class de_cell {
private:
    Inst* inst;

public:
    Inst* get_inst () { return inst; }
    void set_inst (Inst* i) { inst = i; }
};

// Cell connecting execute and memory stages
struct em_cell {};

// Cell connecting memory and writeback stages
struct mw_cell {};

//--------------------------------------------------------------------------
// Hart
//--------------------------------------------------------------------------
class Hart final {
private:
    Memory memory;
    Regfile regfile;
    Reg pc;

    Decoder  decoder;

    void fetch ();
    fd_cell fd;
    void decode ();
    de_cell de;
    void execute ();
    em_cell em;
    void memory_access ();
    mw_cell mw;
    void write_back ();

public:
    void save_in_memory (Segment& segment);
    void load_from_memory (uint64_t vaddr, void* load_ptr, int load_size);
    void memory_dump () { memory.dump (); }
    
    inline void set_reg_val (uint8_t reg, uint64_t v) { regfile.set_reg_val (reg, v); }
    inline uint64_t get_reg_val (uint8_t reg) { return regfile.get_reg_val (reg); }
    inline uint64_t get_pc_val () { return pc.get_val (); }

    void run_pipeline ();

    Hart () {
        pc.set_val (START_ADDRESS);
        regfile.regs[0].set_val (0);
    }
};