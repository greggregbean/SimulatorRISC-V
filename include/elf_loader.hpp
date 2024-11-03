#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include <cstdint>

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
    uint8_t* file_begin;
    Elf64_Off file_offset;
    Elf64_Word flags;

public:
    Segment(GElf_Phdr& curr_segment, uint8_t* elf_buf):
        vaddr(curr_segment.p_vaddr),
        size(curr_segment.p_filesz),
        file_begin(elf_buf),
        file_offset(curr_segment.p_offset),
        flags(curr_segment.p_flags) {}
};
