#pragma once

#include <iostream>

#include "memory.hpp"
#include "execution.hpp"
#include "decoder.hpp"
#include "core/regfile.hpp"
#include "core/segment.hpp"

class fd_cell {
private:
    uint32_t inst;

public:
    uint32_t get_inst () { return inst; }
    void set_inst (uint32_t i) { inst = i; }
};

class de_cell {
private:
    Inst* inst;

public:
    Inst* get_inst () { return inst; }
    void set_inst (Inst* i) { inst = i; }
};

struct em_cell {};

struct mw_cell {};

class Hart final {
private:
    Regfile regfile;
    Reg pc;

    Decoder decoder;
    Memory memory;

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