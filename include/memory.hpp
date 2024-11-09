#pragma once 

#include "regfile.hpp"
#include "utils/constants.hpp"

class Memory {
private:
    int mem_size  = 0;
    int curr_size = 0;
    std::byte* mem = nullptr;

public:
    Memory(int size = DEFAULT_MEM_SIZE): mem_size(size) {
        mem = new std::byte[mem_size];
    }
    ~Memory() {
        delete[] mem;
    }

    void mem_store(uint64_t offset, void* ptr, int ptr_size);
    void mem_load(uint64_t offset, void* ptr, int ptr_size);
    void dump();
};