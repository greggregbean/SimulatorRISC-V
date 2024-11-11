#pragma once

#include <gelf.h>
#include <libelf.h>

#include "hart.hpp"

class ELFLoader {
private:
    std::string file_path;
    int file_size = 0;
public:
    ELFLoader(std::string path): file_path(path) {}
    void load(Hart& hart);
};

class Segment {
    Elf64_Xword vaddr;
    Elf64_Xword size;
    uint8_t* data;
    Elf64_Word flags;

public:
    Segment(GElf_Phdr& curr_segment, uint8_t* elf_buf):
        vaddr(curr_segment.p_vaddr),
        size(curr_segment.p_filesz),
        data(elf_buf + curr_segment.p_offset),
        flags(curr_segment.p_flags) {}

    void* get_data() {
        return data;
    }

    int get_size() {
        return size;
    }

    uint64_t get_vaddr() {
        return vaddr;
    }

    uint8_t get_flag() {
        return flags;
    }
};
