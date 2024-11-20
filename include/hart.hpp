#pragma once

#include <iostream>

// Core
#include "core/regfile.hpp"
#include "core/segment.hpp"

// Include stages
#include "memory.hpp"
#include "stages/decoder.hpp"
#include "stages/executor.hpp"

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
    Executor executor;

    void fetch();
    fd_cell fd;
    void decode();
    de_cell de;
    void execute();
    em_cell em;
    void memory_access();
    mw_cell mw;
    void write_back();

public:
    void save_in_memory (Segment& segment);
    void load_from_memory (uint64_t vaddr, void* load_ptr, int load_size);
    void run_pipeline();
    void memory_dump() { memory.dump (); }

    Hart () {
        pc.set_val (START_ADDRESS);
        regfile.regs[0].set_val (0);
    }
};