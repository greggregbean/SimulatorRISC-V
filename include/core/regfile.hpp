#pragma once

#include <iostream>
#include <iomanip>
#include <array>
#include <cstdint>

//--------------------------------------------------------------------------
// Reg
//--------------------------------------------------------------------------
class Reg final {
private:
    uint64_t val = 0;

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

    void dump () {
        for (int i = 0; i < 32; i++) {
            uint64_t val = get_reg_val (i);

            std::cout << std::dec << "x_" << std::setfill ('0') << std::setw(2) << i
                      << " [";

            if (val != 0)
                std::cout << "\033[32m";

            std::cout << std::setw(20) << val << "\033[0m] " << "(";

            if (val != 0)
                std::cout << "\033[32m";

            std::cout << "0x" << std::setw(16) << std::hex << val << "\033[0m)" << std::endl;
        }
    }
};