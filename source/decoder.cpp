#include "decoder.hpp"

/*
|31    25||24   20||19   15||14    12||11   7||6      0| 
[ funct7 ][  rs2  ][  rs1  ][ funct3 ][  rd  ][ opcode ]
*/

Inst* Decoder::decode_inst (uint32_t inst) {
    int32_t funct7  = (inst >> 25) & 0b1111111;
    int32_t num_rs2 = (inst >> 20) & 0b11111;
    int32_t num_rs1 = (inst >> 15) & 0b11111;
    int32_t funct3  = (inst >> 12) & 0b111;
    int32_t num_rd  = (inst >> 7)  & 0b11111;
    int32_t opcode  = inst         & 0b1111111;
    

    recognize_inst (opcode, funct3, funct7);
}