#pragma once

#include <array>
#include <cstdint>

class Reg final {
private:
    uint64_t val;
public:
    uint64_t get_val () { return val; }
    void set_val (uint64_t v) { val = v; }
};

class Regfile final {
private:
    std::array<Reg, 32> regs;
};