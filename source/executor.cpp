#include "stages/executor.hpp"
#include "hart.hpp"

//--------------------------------------------------------------------------
// Auxiliary functions
//--------------------------------------------------------------------------
inline uint64_t sext_imm12 (uint32_t imm) {
    if (!(imm & (1 << 11)))
        return imm;
    
    return uint64_t(imm) + 0xFFFFFFFFFFFFF000;
}

inline uint64_t sext_imm20 (uint32_t imm) {
    if (!(imm & (1 << 19)))
        return imm;
    
    return uint64_t(imm) + 0xFFFFFFFFFFF00000;
}

//--------------------------------------------------------------------------
// RV32I Base Instruction Set
//--------------------------------------------------------------------------
void Executor::execute_LUI (Inst* inst, Hart& hart) {
    Inst_U* inst_U = static_cast<Inst_U*> (inst);

    uint64_t imm_val = inst_U->get_imm() << 12;

    hart.set_reg_val (inst_U->get_rd(), imm_val);
}

void Executor::execute_AUIPC (Inst* inst, Hart& hart) {
    Inst_U* inst_U = static_cast<Inst_U*> (inst);

    uint64_t imm_val = inst_U->get_imm() << 12;
    // As now inst is on execution stage, and fetch has
    // been already executed 2 times, it means that addr
    // of inst is cur_pc - WORDSIZE*2
    uint64_t pc_val  = hart.get_pc_val() - WORD_SIZE*2;

    hart.set_reg_val (inst_U->get_rd(), pc_val + imm_val);
}

void Executor::execute_JAL (Inst* inst, Hart& hart) {
    Inst_J* inst_J = static_cast<Inst_J*> (inst);

    uint64_t offset = sext_imm20 (inst_J->get_imm() << 1);
    // As now inst is on execution stage, and fetch has
    // been already executed 2 times, it means that addr
    // of inst is cur_pc - WORDSIZE*2
    uint64_t pc_val = hart.get_pc_val() - WORD_SIZE*2;

    // NOTE: If an instruction access-fault or instruction 
    // page-fault exception occurs on the target of a jump or
    // taken branch, the exception is reported on the target 
    // instruction, not on the jump or branch instruction.

    uint64_t target_addr = pc_val + offset;

    // TODO: The JAL and JALR instructions will generate an 
    // instruction-address-misaligned exception if the target
    // address is not aligned to a four-byte boundary.
    if ((target_addr % WORD_SIZE) != 0)
        return;

    hart.set_pc_val (target_addr);
    hart.set_reg_val (inst_J->get_rd(), pc_val + WORD_SIZE);
}

void Executor::execute_JALR (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());
    uint64_t offset = (rs1_val + imm_val) & ~1;

    // As now inst is on execution stage, and fetch has
    // been already executed 2 times, it means that addr
    // of inst is cur_pc - WORDSIZE*2
    uint64_t pc_val = hart.get_pc_val() - WORD_SIZE*2;

    // NOTE: If an instruction access-fault or instruction 
    // page-fault exception occurs on the target of a jump or
    // taken branch, the exception is reported on the target 
    // instruction, not on the jump or branch instruction.

    uint64_t target_addr = pc_val + offset;

    // TODO: The JAL and JALR instructions will generate an 
    // instruction-address-misaligned exception if the target
    // address is not aligned to a four-byte boundary.
    if ((target_addr % WORD_SIZE) != 0)
        return;

    hart.set_pc_val (target_addr);
    hart.set_reg_val (inst_I->get_rd(), pc_val + WORD_SIZE);
}

void Executor::execute_BEQ (Inst* inst, Hart& hart) {
    Inst_B* inst_B = static_cast<Inst_B*> (inst);

    
}

void Executor::execute_BNE (Inst* inst, Hart& hart) {

}

void Executor::execute_BLT (Inst* inst, Hart& hart) {

}

void Executor::execute_BGE (Inst* inst, Hart& hart) {

}

void Executor::execute_BLTU (Inst* inst, Hart& hart) {

}

void Executor::execute_BGEU (Inst* inst, Hart& hart) {

}

void Executor::execute_LB (Inst* inst, Hart& hart) {

}

void Executor::execute_LH (Inst* inst, Hart& hart) {

}

void Executor::execute_LW (Inst* inst, Hart& hart) {

}

void Executor::execute_LBU (Inst* inst, Hart& hart) {

}

void Executor::execute_LHU (Inst* inst, Hart& hart) {

}

void Executor::execute_SB (Inst* inst, Hart& hart) {

}

void Executor::execute_SH (Inst* inst, Hart& hart) {

}

void Executor::execute_SW (Inst* inst, Hart& hart) {

}

void Executor::execute_ADDI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val + imm_val);
}

void Executor::execute_SLTI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    int64_t imm_val = sext_imm12 (inst_I->get_imm());
    int64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    if (rs1_val < imm_val)
        hart.set_reg_val (inst_I->get_rd(), 1);
    
    else 
        hart.set_reg_val (inst_I->get_rd(), 0);
}

void Executor::execute_SLTIU (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    if (rs1_val < imm_val)
        hart.set_reg_val (inst_I->get_rd(), 1);
    
    else 
        hart.set_reg_val (inst_I->get_rd(), 0);
}

void Executor::execute_XORI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val ^ imm_val);
}

void Executor::execute_ORI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val | imm_val);
}

void Executor::execute_ANDI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint64_t imm_val = sext_imm12 (inst_I->get_imm());
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val & imm_val);
}

void Executor::execute_ADD (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val + rs2_val);
}

void Executor::execute_SUB (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val - rs2_val);
}

void Executor::execute_SLL (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint8_t shamt = hart.get_reg_val (inst_R->get_rs2()) & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val << shamt);
}

void Executor::execute_SLT (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    if (rs1_val < rs2_val)
        hart.set_reg_val (inst_R->get_rd(), 1);
    
    else 
        hart.set_reg_val (inst_R->get_rd(), 0);
}

void Executor::execute_SLTU (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    int64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    int64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    if (rs1_val < rs2_val)
        hart.set_reg_val (inst_R->get_rd(), 1);
    
    else 
        hart.set_reg_val (inst_R->get_rd(), 0);
}

void Executor::execute_XOR (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val ^ rs2_val);
}

void Executor::execute_SRL (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint8_t shamt = hart.get_reg_val (inst_R->get_rs2()) & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val >> shamt);
}

void Executor::execute_SRA (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint8_t shamt = hart.get_reg_val (inst_R->get_rs2()) & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    // As right shift may fill "empty" bits with the original MSB 
    // (i.e. perform sign extension) or it may shift in zeroes, 
    // depending on platform and/or compiler, we made sign extension
    // for SRAI explicitly. 
    if (!(rs1_val & (1 << 63)))
        hart.set_reg_val (inst_R->get_rd(), rs1_val >> shamt);
    
    else {
        for (uint8_t i = 0; i < shamt; i++) {
            rs1_val >>= 1;
            rs1_val |= (1 << 63);
        }
        
        hart.set_reg_val (inst_R->get_rd(), rs1_val);
    }
}

void Executor::execute_OR (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val | rs2_val);
}

void Executor::execute_AND (Inst* inst, Hart& hart) {
    Inst_R* inst_R = static_cast<Inst_R*> (inst);

    uint64_t rs2_val = hart.get_reg_val (inst_R->get_rs2());
    uint64_t rs1_val = hart.get_reg_val (inst_R->get_rs1());

    hart.set_reg_val (inst_R->get_rd(), rs1_val & rs2_val);
}

void Executor::execute_FENCE (Inst* inst, Hart& hart) {

}

void Executor::execute_FENCE_TSO (Inst* inst, Hart& hart) {

}

void Executor::execute_PAUSE (Inst* inst, Hart& hart) {

}

void Executor::execute_ECALL (Inst* inst, Hart& hart) {

}

void Executor::execute_EBREAK (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV64I Base Instruction Set (in addition to RV32I)
//--------------------------------------------------------------------------
void Executor::execute_LWU (Inst* inst, Hart& hart) {

}

void Executor::execute_LD (Inst* inst, Hart& hart) {

}

void Executor::execute_SD (Inst* inst, Hart& hart) {

}

void Executor::execute_SLLI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint8_t shamt = inst_I->get_imm() & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val << shamt);
}

void Executor::execute_SRLI (Inst* inst, Hart& hart) {
    Inst_I* inst_I = static_cast<Inst_I*> (inst);

    uint8_t shamt = inst_I->get_imm() & 0b111111;
    uint64_t rs1_val = hart.get_reg_val (inst_I->get_rs1());

    hart.set_reg_val (inst_I->get_rd(), rs1_val >> shamt);
}

void Executor::execute_SRAI (Inst* inst, Hart& hart) {
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
        for (uint8_t i = 0; i < shamt; i++) {
            rs1_val >>= 1;
            rs1_val |= (1 << 63);
        }
        
        hart.set_reg_val (inst_I->get_rd(), rs1_val);
    }
}

void Executor::execute_ADDIW (Inst* inst, Hart& hart) {

}

void Executor::execute_SLLIW (Inst* inst, Hart& hart) {

}

void Executor::execute_SRLIW (Inst* inst, Hart& hart) {

}

void Executor::execute_SRAIW (Inst* inst, Hart& hart) {

}

void Executor::execute_ADDW (Inst* inst, Hart& hart) {

}

void Executor::execute_SUBW (Inst* inst, Hart& hart) {

}

void Executor::execute_SLLW (Inst* inst, Hart& hart) {

}

void Executor::execute_SRLW (Inst* inst, Hart& hart) {

}

void Executor::execute_SRAW (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV32/RV64 Zifencei Standard Extension
//--------------------------------------------------------------------------
void Executor::execute_FENCE_I (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV32/RV64 Zicsr Standard Extension
//--------------------------------------------------------------------------
void Executor::execute_CSRRW (Inst* inst, Hart& hart) {

}

void Executor::execute_CSRRS (Inst* inst, Hart& hart) {

}

void Executor::execute_CSRRC (Inst* inst, Hart& hart) {

}

void Executor::execute_CSRRWI (Inst* inst, Hart& hart) {

}

void Executor::execute_CSRRSI (Inst* inst, Hart& hart) {

}

void Executor::execute_CSRRCI (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV32M Standard Extension
//--------------------------------------------------------------------------
void Executor::execute_MUL (Inst* inst, Hart& hart) {

}

void Executor::execute_MULH (Inst* inst, Hart& hart) {

}

void Executor::execute_MULHSU (Inst* inst, Hart& hart) {

}

void Executor::execute_MULHU (Inst* inst, Hart& hart) {

}

void Executor::execute_DIV (Inst* inst, Hart& hart) {

}

void Executor::execute_DIVU (Inst* inst, Hart& hart) {

}

void Executor::execute_REM (Inst* inst, Hart& hart) {

}

void Executor::execute_REMU (Inst* inst, Hart& hart) {

}

//--------------------------------------------------------------------------
// RV64M Standard Extension (in addition to RV32M)
//--------------------------------------------------------------------------
void Executor::execute_MULW (Inst* inst, Hart& hart) {

}

void Executor::execute_DIVW (Inst* inst, Hart& hart) {

}

void Executor::execute_DIVUW (Inst* inst, Hart& hart) {

}

void Executor::execute_REMW (Inst* inst, Hart& hart) {

}

void Executor::execute_REMUW (Inst* inst, Hart& hart) {

}