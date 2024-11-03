#pragma once

#include "regfile.hpp"
#include "decoder.hpp"

class Hart final {
    Regfile regfile;
    Reg pc;

    Decoder decoder;
};