#pragma once

#include "memory.hpp"
#include "decoder.hpp"

class Segment;

class Hart final {
private:
    Regfile regfile;
    Reg pc;

    Decoder decoder;
    Memory memory{};

public:
    void save_in_memory(Segment& segment);
    void load_from_memory(uint64_t vaddr, void* load_ptr, int load_size);
    void memory_dump() { memory.dump(); }
};