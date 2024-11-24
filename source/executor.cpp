#include "stages/executor.hpp"
#include "hart.hpp"

//--------------------------------------------------------------------------
// RV32I Base Instruction Set
//--------------------------------------------------------------------------
void execute_LUI (Inst* inst, Hart& hart) {
    Inst_U* inst_U = static_cast<Inst_U*> (inst);

    uint64_t imm_val = inst_U->get_imm() << 12;

    hart.set_reg_val (inst_U->get_rd(), imm_val);
}

void execute_AUIPC (Inst* inst, Hart& hart) {
    Inst_U* inst_U = static_cast<Inst_U*> (inst);

    uint64_t imm_val = inst_U->get_imm() << 12;
    // As now AUPC is on execution stage, and fetch has
    // been already executed 2 times, it means that addr
    // of AUPC is cur_pc - WORDSIZE*2
    uint64_t pc_val  = hart.get_pc_val() - WORD_SIZE*2;

    hart.set_reg_val (inst_U->get_rd(), pc_val + imm_val);
}

void execute_JAL (Inst* inst, Hart& hart) {
}

void execute_JALR (Inst* inst, Hart& hart) {
}

void execute_BEQ (Inst* inst, Hart& hart) {
}

void execute_BNE (Inst* inst, Hart& hart) {

}

void execute_BLT (Inst* inst, Hart& hart) {

}

void execute_BGE (Inst* inst, Hart& hart) {

}

void execute_BLTU (Inst* inst, Hart& hart) {

}

void execute_BGEU (Inst* inst, Hart& hart) {

}

void execute_LB (Inst* inst, Hart& hart) {

}

void execute_LH (Inst* inst, Hart& hart) {

}

void execute_LW (Inst* inst, Hart& hart) {

}

void execute_LBU (Inst* inst, Hart& hart) {

}

void execute_LHU (Inst* inst, Hart& hart) {

}

void execute_SB (Inst* inst, Hart& hart) {

}

void execute_SH (Inst* inst, Hart& hart) {

}

void execute_SW (Inst* inst, Hart& hart) {

}

void execute_ADDI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val + imm_val);
}

void execute_SLTI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    int64_t imm_val = sext_imm12 (inst_I->get_imm());
    int64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    if (rs1_val < imm_val)
        hart.set_reg_val (inst_I->get_rd(), 1);
    
    else 
        hart.set_reg_val (inst_I->get_rd(), 0);
}

void execute_SLTIU (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    if (rs1_val < imm_val)
        hart.set_reg_val (inst_I->get_rd(), 1);
    
    else 
        hart.set_reg_val (inst_I->get_rd(), 0);
}

void execute_XORI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val ^ imm_val);
}

void execute_ORI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val | imm_val);
}

void execute_ANDI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val & imm_val);
}

void execute_ADD (Inst* inst, Hart& hart) {


}

void execute_SUB (Inst* inst, Hart& hart) {

}

void execute_SLL (Inst* inst, Hart& hart) {

}

void execute_SLT (Inst* inst, Hart& hart) {

}

void execute_SLTU (Inst* inst, Hart& hart) {

}

void execute_XOR (Inst* inst, Hart& hart) {

}

void execute_SRL (Inst* inst, Hart& hart) {

}

void execute_SRA (Inst* inst, Hart& hart) {

}

void execute_OR (Inst* inst, Hart& hart) {

}

void execute_AND (Inst* inst, Hart& hart) {

}

void execute_FENCE (Inst* inst, Hart& hart) {

}

void execute_FENCE_TSO (Inst* inst, Hart& hart) {

}

void execute_PAUSE (Inst* inst, Hart& hart) {

}

void execute_ECALL (Inst* inst, Hart& hart) {

}

void execute_EBREAK (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV64I Base Instruction Set (in addition to RV32I)
//--------------------------------------------------------------------------
void execute_LWU (Inst* inst, Hart& hart) {

}

void execute_LD (Inst* inst, Hart& hart) {

}

void execute_SD (Inst* inst, Hart& hart) {

}

void execute_SLLI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint8_t shamt = inst_I->get_imm() & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val << shamt);
}

void execute_SRLI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint8_t shamt = inst_I->get_imm() & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val >> shamt);
}

void execute_SRAI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint8_t shamt = inst_I->get_imm() & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    // As right shift may fill "empty" bits with the original MSB 
    // (i.e. perform sign extension) or it may shift in zeroes, 
    // depending on platform and/or compiler, we made sign extension
    // for SRAI explicitly. 
    if (!(rs1_val & (1 << 63)))
        hart.set_reg_val (inst_I->get_rd(), rs1_val >> shamt);
    
    else {
        uint64_t rd_val = rs1_val;

        for (uint8_t i = 0; i < shamt; i++) {
            rd_val >>= 1;
            rd_val |= (1 << 63);
        }
        
        hart.set_reg_val (inst_I->get_rd(), rd_val);
    }
}

void execute_ADDIW (Inst* inst, Hart& hart) {

}

void execute_SLLIW (Inst* inst, Hart& hart) {

}

void execute_SRLIW (Inst* inst, Hart& hart) {

}

void execute_SRAIW (Inst* inst, Hart& hart) {

}

void execute_ADDW (Inst* inst, Hart& hart) {

}

void execute_SUBW (Inst* inst, Hart& hart) {

}

void execute_SLLW (Inst* inst, Hart& hart) {

}

void execute_SRLW (Inst* inst, Hart& hart) {

}

void execute_SRAW (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV32/RV64 Zifencei Standard Extension
//--------------------------------------------------------------------------
void execute_FENCE_I (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV32/RV64 Zicsr Standard Extension
//--------------------------------------------------------------------------
void execute_CSRRW (Inst* inst, Hart& hart) {

}

void execute_CSRRS (Inst* inst, Hart& hart) {

}

void execute_CSRRC (Inst* inst, Hart& hart) {

}

void execute_CSRRWI (Inst* inst, Hart& hart) {

}

void execute_CSRRSI (Inst* inst, Hart& hart) {

}

void execute_CSRRCI (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV32M Standard Extension
//--------------------------------------------------------------------------
void execute_MUL (Inst* inst, Hart& hart) {

}

void execute_MULH (Inst* inst, Hart& hart) {

}

void execute_MULHSU (Inst* inst, Hart& hart) {

}

void execute_MULHU (Inst* inst, Hart& hart) {

}

void execute_DIV (Inst* inst, Hart& hart) {

}

void execute_DIVU (Inst* inst, Hart& hart) {

}

void execute_REM (Inst* inst, Hart& hart) {

}

void execute_REMU (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV64M Standard Extension (in addition to RV32M)
//--------------------------------------------------------------------------
void execute_MULW (Inst* inst, Hart& hart) {

}

void execute_DIVW (Inst* inst, Hart& hart) {

}

void execute_DIVUW (Inst* inst, Hart& hart) {

}

void execute_REMW (Inst* inst, Hart& hart) {

}

void execute_REMUW (Inst* inst, Hart& hart) {

}