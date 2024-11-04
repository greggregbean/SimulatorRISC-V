#include "regfile.hpp"

#include <cstring>

int DEFAULT_MEM_SIZE = 1 << 25;

class Memory {
private:
    int mem_size = 0;
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
};