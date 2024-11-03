#pragma once

#include "inst.hpp"
#include "regfile.hpp"

class Decoder
{
    InstType cur_inst_type = InstType::NONE;
    InstName cur_inst_name = InstName::NONE;

    void recognize_inst (uint32_t opcode, uint32_t funct3, uint32_t funct7);
    
public:
    Inst* decode_inst (uint32_t inst);

};