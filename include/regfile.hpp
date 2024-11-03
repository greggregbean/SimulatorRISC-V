#pragma once

#include <array>
#include <cstdint>

class Reg final {
    int32_t val;
public:
    int32_t get_val () { return val; }
    void set_val (int32_t v) { val = v; }
};

class Regfile final {
    std::array<Reg, 32> regs;
};