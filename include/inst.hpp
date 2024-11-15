#pragma once

#include <cstdint>

#include "regfile.hpp"

enum class Opcode : uint8_t {
    LUI      = 0b0110111,
    AUIPC    = 0b0010111,
    JAL      = 0b1101111,
    JALR     = 0b1100111,
    B        = 0b1100011,
    L        = 0b0000011,
    S        = 0b0100011,
    A_I      = 0b0010011,
    A        = 0b0110011,
    F        = 0b0001111,
    E        = 0b1110011,
    A_I_W    = 0b0011011,
    A_W      = 0b0111011,

    NONE
};

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
    // RV32I Base Instruction Set
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
    //SLLI,  <- in RV64I Base Instruction Set
    //SRLI,  <- in RV64I Base Instruction Set
    //SRAI,  <- in RV64I Base Instruction Set
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
    FENCE_TSO,
    PAUSE,
    ECALL,
    EBREAK,

    // RV64I Base Instruction Set
    LWU,
    LD,
    SD,
    SLLI,
    SRLI,
    SRAI,
    ADDIW,
    SLLIW,
    SRLIW,
    SRAIW,
    ADDW,
    SUBW,
    SLLW,
    SRLW,
    SRAW,

    NONE
};

class Inst {
private:
    friend class Decoder;

    InstType type = InstType::NONE;
    InstName name = InstName::NONE;
    Opcode opcode = Opcode::NONE;
    
    void (*executor) (Inst*) = nullptr;

public:
    virtual ~Inst() = 0;
}; 

class Inst_R final : public Inst {
private:
    friend class Decoder;

    uint8_t funct7;
    uint8_t rs2;
    uint8_t rs1;
    uint8_t funct3;
    uint8_t rd;
}; 

class Inst_I final : public Inst {
private:
    friend class Decoder;

    uint32_t imm;
    uint8_t  rs1;
    uint8_t  funct3;
    uint8_t  rd;
}; 

class Inst_S final : public Inst {
private:
    friend class Decoder;

    uint32_t imm;
    uint8_t  rs2;
    uint8_t  rs1;
    uint8_t  funct3;
}; 

class Inst_B final : public Inst {
private:
    friend class Decoder;

    uint32_t imm;
    uint8_t  rs2;
    uint8_t  rs1;
    uint8_t  funct3;
}; 

class Inst_U final : public Inst {
private:
    friend class Decoder;

    uint32_t imm;
    uint8_t  rd;      
}; 

class Inst_J final : public Inst {
private:
    friend class Decoder;

    uint32_t imm;
    uint8_t  rd;
}; 