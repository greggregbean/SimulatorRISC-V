#pragma once

#include "core/inst.hpp"

namespace Executor {  
    // RV32I Base Instruction Set
    void execute_LUI (Inst* inst);
    void execute_AUIPC (Inst* inst);
    void execute_JAL (Inst* inst);
    void execute_JALR (Inst* inst);
    void execute_BEQ (Inst* inst);
    void execute_BNE (Inst* inst);
    void execute_BLT (Inst* inst);
    void execute_BGE (Inst* inst);
    void execute_BLTU (Inst* inst);
    void execute_BGEU (Inst* inst);
    void execute_LB (Inst* inst);
    void execute_LH (Inst* inst);
    void execute_LW (Inst* inst);
    void execute_LBU (Inst* inst);
    void execute_LHU (Inst* inst);
    void execute_SB (Inst* inst);
    void execute_SH (Inst* inst);
    void execute_SW (Inst* inst);
    void execute_ADDI (Inst* inst);
    void execute_SLTI (Inst* inst);
    void execute_SLTIU (Inst* inst);
    void execute_XORI (Inst* inst);
    void execute_ORI (Inst* inst);
    void execute_ANDI (Inst* inst);
    void execute_ADD (Inst* inst);
    void execute_SUB (Inst* inst);
    void execute_SLL (Inst* inst);
    void execute_SLT (Inst* inst);
    void execute_SLTU (Inst* inst);
    void execute_XOR (Inst* inst);
    void execute_SRL (Inst* inst);
    void execute_SRA (Inst* inst);
    void execute_OR (Inst* inst);
    void execute_AND (Inst* inst);
    void execute_FENCE (Inst* inst);
    void execute_FENCE_TSO (Inst* inst);
    void execute_PAUSE (Inst* inst);
    void execute_ECALL (Inst* inst);
    void execute_EBREAK (Inst* inst);

    // RV64I Base Instruction Set (in addition to RV32I)
    void execute_LWU (Inst* inst);
    void execute_LD (Inst* inst);
    void execute_SD (Inst* inst);
    void execute_SLLI (Inst* inst);
    void execute_SRLI (Inst* inst);
    void execute_SRAI (Inst* inst);
    void execute_ADDIW (Inst* inst);
    void execute_SLLIW (Inst* inst);
    void execute_SRLIW (Inst* inst);
    void execute_SRAIW (Inst* inst);
    void execute_ADDW (Inst* inst);
    void execute_SUBW (Inst* inst);
    void execute_SLLW (Inst* inst);
    void execute_SRLW (Inst* inst);
    void execute_SRAW (Inst* inst);

    // RV32/RV64 Zifencei Standard Extension
    void execute_FENCE_I (Inst* inst);

    // RV32/RV64 Zicsr Standard Extension
    void execute_CSRRW (Inst* inst);
    void execute_CSRRS (Inst* inst);
    void execute_CSRRC (Inst* inst);
    void execute_CSRRWI (Inst* inst);
    void execute_CSRRSI (Inst* inst);
    void execute_CSRRCI (Inst* inst);

    // RV32M Standard Extension
    void execute_MUL (Inst* inst);
    void execute_MULH (Inst* inst);
    void execute_MULHSU (Inst* inst);
    void execute_MULHU (Inst* inst);
    void execute_DIV (Inst* inst);
    void execute_DIVU (Inst* inst);
    void execute_REM (Inst* inst);
    void execute_REMU (Inst* inst);

    // RV64M Standard Extension (in addition to RV32M)
    void execute_MULW (Inst* inst);
    void execute_DIVW (Inst* inst);
    void execute_DIVUW (Inst* inst);
    void execute_REMW (Inst* inst);
    void execute_REMUW (Inst* inst);
};