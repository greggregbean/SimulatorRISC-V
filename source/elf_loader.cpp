#include "../include/elf_loader.hpp"

void ELFLoader::Load() {
    //open the elf file
    int elf_file = open(file_path.c_str(), O_RDONLY);
    assert(elf_file != 0 && "there is no such elf-file");
    
    //get the elf file size
    file_size = lseek(elf_file, 0, SEEK_END);
    assert(file_size > 0 && "elf-file is empty");
    lseek(elf_file, 0, SEEK_SET);

    std::vector<uint8_t> elf_buf(file_size, 0);
    int read_num = read(elf_file, elf_buf.data(), file_size);
    //std::cout << read_num;
    assert(read_num != -1);

    //get elf-file
    Elf* elf = elf_begin(elf_file, ELF_C_READ, nullptr);
    assert(!elf && "elf ptr is incorrect");
    assert(gelf_getclass(elf) != ELFCLASSNONE && "the file is't 64 bit");
    assert(gelf_getclass(elf) != ELFCLASS32 && "the file is 32 bit, 64 bit is required");

    //get file header
    GElf_Ehdr elf_header{};
    assert(!gelf_getehdr(elf, &elf_header) && "can't get the file header");

    int segment_num = elf_header.e_phnum;
    //process segments that are intended to be loaded into memory
    for(int i = 0; i < segment_num; ++i) {
        GElf_Phdr seg_header{};
        assert(!gelf_getphdr(elf, i, &seg_header) && "can't get the file segment");

        if(seg_header.p_type == PT_LOAD) {
            Segment seg(seg_header);
        }
    }
}