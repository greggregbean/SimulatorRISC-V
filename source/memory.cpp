#include "../include/memory.hpp"

void PhysicalMemory::mem_store(uint64_t offset, void* ptr, int ptr_size) {
    std::memcpy(ptr, mem + offset, ptr_size);
}

void PhysicalMemory::mem_load(uint64_t offset, void* ptr, int ptr_size) {
    std::memcpy(mem + offset, ptr, ptr_size);
}
