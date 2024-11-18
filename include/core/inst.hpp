#pragma once

#include <cstdint>

enum class Opcode : uint8_t {
    NONE = 0,

    LUI       = 0b0110111,
    AUIPC     = 0b0010111,
    JAL       = 0b1101111,
    JALR      = 0b1100111,
    BRANCH    = 0b1100011,
    LOAD      = 0b0000011,
    STORE     = 0b0100011,
    OP_IMM    = 0b0010011,
    OP        = 0b0110011,
    MISC_MEM  = 0b0001111,
    SYSTEM    = 0b1110011,
    OP_IMM_32 = 0b0011011, 
    OP_32     = 0b0111011
};

enum class InstType {
    NONE = 0,

    R,
    I,
    S,
    B,
    U,
    J
};

enum class InstName {
    NONE = 0,

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

    // RV64I Base Instruction Set (in addition to RV32I)
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

    // RV32/RV64 Zifencei Standard Extension
    FENCE_I,

    // RV32/RV64 Zicsr Standard Extension
    CSRRW,
    CSRRS,
    CSRRC,
    CSRRWI,
    CSRRSI,
    CSRRCI,

    // RV32M Standard Extension
    MUL,
    MULH,
    MULHSU,
    MULHU,
    DIV,
    DIVU,
    REM,
    REMU,

    // RV64M Standard Extension (in addition to RV32M)
    MULW,
    DIVW,
    DIVUW,
    REMW,
    REMUW
};

class Inst {
private:
    friend class Decoder;

    InstType type = InstType::NONE;
    InstName name = InstName::NONE;
    Opcode opcode = Opcode::NONE;
    
    void (*executor) (Inst*) = nullptr;

public:
    virtual ~Inst() {};
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