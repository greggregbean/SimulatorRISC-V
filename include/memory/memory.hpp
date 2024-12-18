#pragma once 

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <cstddef>

#include "utils/constants.hpp"
#include "utils/macros.hpp"

class Memory {
private:
    uint64_t mem_size  = 0;
    uint64_t curr_size = 0;
    std::byte* mem = nullptr;

    uint64_t pages_controller = 0;

public:
    Memory (int size = DEFAULT_MEM_SIZE): mem_size (size) {
        mem = new std::byte [mem_size];
    }
    ~Memory() {
        delete [] mem;
    }

    NO_COPY_SEMANTIC(Memory);
    NO_MOVE_SEMANTIC(Memory);

    inline uint64_t get_mem_size () { return mem_size; }
    inline uint64_t get_curr_size () { return curr_size; }

    int64_t get_clean_pages(int num = 1);

    void mem_store (uint64_t offset, void* ptr, int ptr_size);
    void mem_load (uint64_t offset, void* ptr, int ptr_size);
    std::byte* get_host_addr (uint64_t paddr);
    void dump ();
    void dump_stack (uint64_t sp);
};