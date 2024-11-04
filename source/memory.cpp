#include "../include/memory.hpp"

void Memory::mem_store(uint64_t offset, void* ptr, int ptr_size) {
    std::memcpy(ptr, mem + offset, ptr_size);
}

void Memory::mem_load(uint64_t offset, void* ptr, int ptr_size) {
    std::memcpy(mem + offset, ptr, ptr_size);
}
