#include "memory/memory.hpp"

void Memory::mem_load (uint64_t offset, void* ptr, int ptr_size) {
    std::memcpy (ptr, mem + offset, ptr_size);
}

void Memory::mem_store (uint64_t offset, void* ptr, int ptr_size) {
    assert (curr_size + offset < mem_size && "there is no more space in the memory");
    curr_size = (offset + ptr_size) > curr_size ? offset + ptr_size 
                                                : curr_size;
    std::memcpy (mem + offset, ptr, ptr_size);
}

std::byte* Memory::get_host_addr(uint64_t paddr) {
    return mem + paddr;
}

int64_t Memory::get_clean_pages(int num) {
    int64_t addr = pages_controller;
    pages_controller += DEFAULT_ALLOC_PAGES_SIZE * num;
    return addr;
}

void Memory::dump () {
    int zero_counter = 0;

    for (uint64_t i = 0; i < curr_size; ++i) {
        if (zero_counter == 32) {
            if (std::to_integer<int>(mem[i]) != 0) {
                std::cout << std::endl << "..." << std::endl;
                zero_counter = 0;
            }
            else
                continue;
        }

        std::cout << std::hex << std::setw (2) << std::setfill('0')
                  << static_cast<int>(mem[i]) << " ";

        if (std::to_integer<int>(mem[i]) == 0)
            zero_counter++;
    }
    std::cout << std::dec << std::endl;
}

void Memory::dump_stack (uint64_t sp) {
    for (uint64_t i = sp; i < mem_size; ++i) {
        std::cout << std::hex << std::setw (2) << std::setfill('0')
                  << static_cast<int>(mem[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}

