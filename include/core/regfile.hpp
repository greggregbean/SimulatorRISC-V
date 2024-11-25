#pragma once

#include <array>
#include <cstdint>

//--------------------------------------------------------------------------
// Reg
//--------------------------------------------------------------------------
class Reg final {
private:
    uint64_t val;

public:
    inline uint64_t get_val () { return val; }
    inline void set_val (uint64_t v) { val = v; }
};

//--------------------------------------------------------------------------
// Regfile
//--------------------------------------------------------------------------
class Regfile final {
private:
    friend class Hart;
    std::array<Reg, 32> regs;

public:
    inline uint64_t get_reg_val (uint8_t reg) { return regs[reg].get_val(); }
    inline void set_reg_val (uint8_t reg, uint64_t v) { regs[reg].set_val (v); }
};