#pragma once

#include <iostream>

#include "memory.hpp"
#include "decoder.hpp"

class Segment;

class Hart final {
private:
    Regfile regfile;
    Reg pc;

    Decoder decoder;
    Memory memory;

    void fetch();
    void decode();
    void execute();
    void memory_access();
    void write_back();

public:
    void save_in_memory (Segment& segment);
    void load_from_memory (uint64_t vaddr, void* load_ptr, int load_size);
    void run_pipeline();
    void memory_dump() { memory.dump (); }
};