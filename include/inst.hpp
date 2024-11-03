#pragma once

#include <cstdint>

#include "regfile.hpp"

enum class InstType {
    R,
    I,
    S,
    B,
    U,
    J,
    NONE
};

enum class InstName {
    LUI,
    AUIPC,
    JAL,
    JALR,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    FENCE,
    FENCE_I,
    ECALL,
    EBREAK,
    CSRRW,
    CSRRS,
    CSRRC,
    CSRRWI,
    CSRRSI,
    CSRRCI,
    NONE
};

class Inst {
    friend class Decoder;

    InstType type = InstType::NONE;
    InstName name = InstName::NONE;
    int32_t opcode;
    void (*inst_executor) (Inst*) = nullptr;

public:
    Inst (InstType t, InstName n) : type (t), name (n) {}
}; 

class Inst_R final : public Inst  {
    friend class Decoder;

    int32_t funct7;
    Reg rs2;
    Reg rs1;
    int32_t funct3;
    Reg rd;

public:
    Inst_R (InstName n) : Inst (InstType::R, n) {}
}; 

class Inst_I final : public Inst  {
    friend class Decoder;

    int32_t imm;
    Reg rs1;
    int32_t funct3;
    Reg rd;

public:
    Inst_I (InstName n) : Inst (InstType::I, n) {}
}; 

class Inst_S final : public Inst  {
    friend class Decoder;

    int32_t imm;
    Reg rs2;
    Reg rs1;
    int32_t funct3;

public:
    Inst_S (InstName n) : Inst (InstType::S, n) {}
}; 

class Inst_B final : public Inst  {
    friend class Decoder;

    int32_t imm;
    Reg rs2;
    Reg rs1;
    int32_t funct3;

public:
    Inst_B (InstName n) : Inst (InstType::B, n) {}
}; 

class Inst_U final : public Inst  {
    friend class Decoder;

    int32_t imm;
    Reg rd;
public:
    Inst_U (InstName n) : Inst (InstType::U, n) {}       
}; 

class Inst_J final : public Inst  {
    friend class Decoder;

    int32_t imm;
    Reg rd;
public:
    Inst_J (InstName n) : Inst (InstType::J, n) {}  
}; 