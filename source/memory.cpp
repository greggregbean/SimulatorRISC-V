#include "../include/memory.hpp"

void Memory::mem_load(uint64_t offset, void* ptr, int ptr_size) {
    std::memcpy(ptr, mem + offset, ptr_size);
}

void Memory::mem_store(uint64_t offset, void* ptr, int ptr_size) {
    assert(curr_size + offset < mem_size && "there is no more space in the memory");
    curr_size = (offset + ptr_size) > curr_size ? offset + ptr_size 
                                                : curr_size;
    std::memcpy(mem + offset, ptr, ptr_size);
}

void Memory::dump() {
    for(int i = 0; i < curr_size; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(mem[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}

