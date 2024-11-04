#pragma once

#include "memory.hpp"
#include "decoder.hpp"

class Segment;

class Hart final {
private:
    Regfile regfile;
    Reg pc;

    Decoder decoder;

    Memory memory{};

public:
    void save_in_memory(Segment& segment);
};