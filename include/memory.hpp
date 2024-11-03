#include "regfile.hpp"

#include <cstring>

class PhysicalMemory {
private:
    int mem_size = 0;
    std::byte* mem = nullptr;

public:
    PhysicalMemory(int size): mem_size(size) {
        mem = new std::byte[mem_size];
    }
    ~PhysicalMemory() {
        delete[] mem;
    }

    void mem_store(uint64_t offset, void* ptr, int ptr_size);
    void mem_load(uint64_t offset, void* ptr, int ptr_size);
};