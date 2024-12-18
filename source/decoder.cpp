#include "stages/decoder.hpp"
#include "stages/decode_map.hpp"
#include "stages/executor.hpp"

//--------------------------------------------------------------------------
// Auxiliary functions
//--------------------------------------------------------------------------
inline uint32_t Decoder::decode_imm_I (uint32_t inst) {
    return inst >> 20;                                // imm [11:0]
}

inline uint32_t Decoder::decode_imm_S (uint32_t inst) {
    return ((inst >>  7) & 0b11111)          |        // imm [4:0]
           (((inst >> 25) & 0b1111111) << 5) ;        // imm [11:5] 
}

inline uint32_t Decoder::decode_imm_B (uint32_t inst) {
    return (((inst >> 8)  & 0b1111)   << 1)  |        // imm [4:1]
           (((inst >> 25) & 0b111111) << 5)  |        // imm [5:10]
           (((inst >> 7)  & 0b1)      << 11) |        // imm [11]
           (((inst >> 31) & 0b1)      << 12) ;        // imm [12]
}

inline uint32_t Decoder::decode_imm_U (uint32_t inst) {
    return inst >> 12;                               // imm [31:12]
}

inline uint32_t Decoder::decode_imm_J (uint32_t inst) {
    return (((inst >> 21) & 0b1111111111) << 1)  |    // imm [10:1]
           (((inst >> 20) & 0b1)          << 11) |    // imm [11]
           (((inst >> 12) & 0b11111111)   << 12) |    // imm [19:12]
           (((inst >> 31) & 0b1)          << 20) ;    // imm [20]
}

inline uint8_t Decoder::decode_funct7 (uint32_t inst) {
    return (inst >> 25) & 0b1111111;                // inst [31:25]
}

inline uint8_t Decoder::decode_rs2 (uint32_t inst) {
    return (inst >> 20) & 0b11111;                  // inst [24:20]
}

inline uint8_t Decoder::decode_rs1 (uint32_t inst) {
    return (inst >> 15) & 0b11111;                  // inst [19:15]
}

inline uint8_t Decoder::decode_funct3 (uint32_t inst) {
    return (inst >> 12) & 0b111;                    // inst [14:12]
}

inline uint8_t Decoder::decode_rd (uint32_t inst) {
    return (inst >> 7) & 0b11111;                   // inst [11:7]
}

inline uint8_t Decoder::decode_opcode (uint32_t inst) {
    return inst & 0b1111111;                        // inst [6:0]
}

//--------------------------------------------------------------------------
// Decode_inst
//--------------------------------------------------------------------------
// Recognize instruction using special maps, relying on opcode, funct3 and 
// funct7 and set appropriate execute_func
InstType Decoder::decode_inst_map (uint32_t inst) {
    uint8_t funct7 = decode_funct7 (inst);
    uint8_t funct3 = decode_funct3 (inst);
    uint8_t opcode = decode_opcode (inst);

    InstName inst_name;
    InstType inst_type;

    funct3_map& f3_m = opc_m [opcode];
    if (!f3_m.valid)
        inst_name = f3_m.inst_name;
    
    else {
        funct7_map& f7_m = f3_m.map [funct3];
        if (!f7_m.valid)
            inst_name = f7_m.inst_name;
        
        else
            inst_name = f7_m.map [funct7];
    }

    inst_type = opcode_type_map [opcode];

    switch (inst_type) {
        case InstType::R:
            d_cell.tmp_inst_R.execute_func = name_executor_map [inst_name];
            d_cell.tmp_inst_R.type   = InstType::R;
            d_cell.tmp_inst_R.rs2    = decode_rs2 (inst);
            d_cell.tmp_inst_R.rs1    = decode_rs1 (inst);
            d_cell.tmp_inst_R.rd     = decode_rd (inst);
            break;
        
        case InstType::I:
            d_cell.tmp_inst_I.execute_func = name_executor_map [inst_name];
            d_cell.tmp_inst_I.type   = InstType::I;
            d_cell.tmp_inst_I.imm    = decode_imm_I (inst);
            d_cell.tmp_inst_I.rs1    = decode_rs1 (inst);
            d_cell.tmp_inst_I.rd     = decode_rd (inst);
            break;
        
        case InstType::S:
            d_cell.tmp_inst_S.execute_func = name_executor_map [inst_name];
            d_cell.tmp_inst_S.type   = InstType::S;
            d_cell.tmp_inst_S.imm    = decode_imm_S (inst);
            d_cell.tmp_inst_S.rs2    = decode_rs2 (inst);
            d_cell.tmp_inst_S.rs1    = decode_rs1 (inst);
            break;
        
        case InstType::B:
            d_cell.tmp_inst_B.execute_func = name_executor_map [inst_name];
            d_cell.tmp_inst_B.type   = InstType::B;
            d_cell.tmp_inst_B.imm    = decode_imm_B (inst);
            d_cell.tmp_inst_B.rs2    = decode_rs2 (inst);
            d_cell.tmp_inst_B.rs1    = decode_rs1 (inst);
            break;
        
        case InstType::U:
            d_cell.tmp_inst_U.execute_func = name_executor_map [inst_name];
            d_cell.tmp_inst_U.type   = InstType::U;
            d_cell.tmp_inst_U.imm    = decode_imm_U (inst);
            d_cell.tmp_inst_U.rd     = decode_rd (inst);
            break;
        
        case InstType::J:
            d_cell.tmp_inst_J.execute_func = name_executor_map [inst_name];
            d_cell.tmp_inst_J.type   = InstType::J;
            d_cell.tmp_inst_J.imm    = decode_imm_J (inst);
            d_cell.tmp_inst_J.rd     = decode_rd (inst);
            break;
    }

    return inst_type;
}

//--------------------------------------------------------------------------
// Decode_inst
//--------------------------------------------------------------------------
// Recognize instruction using switch cases, relying on opcode, funct3 and 
// funct7 and set appropriate execute_func
InstType Decoder::decode_inst (uint32_t inst) {
    uint8_t funct7 = decode_funct7 (inst);
    uint8_t funct3 = decode_funct3 (inst);
    uint8_t opc = decode_opcode (inst);

    Opcode opcode = static_cast<Opcode>(opc);
    InstType inst_type = InstType::NONE;

    switch (opcode) {
        case Opcode::LUI:
            d_cell.tmp_inst_U.name = InstName::LUI;
            d_cell.tmp_inst_U.execute_func = Executor::execute_LUI;
            inst_type = InstType::U;
            break;

        case Opcode::AUIPC:
            d_cell.tmp_inst_U.name = InstName::AUIPC;
            d_cell.tmp_inst_U.execute_func = Executor::execute_AUIPC;
            inst_type = InstType::U;
            break;

        case Opcode::JAL:
            d_cell.tmp_inst_J.name = InstName::JAL;
            d_cell.tmp_inst_J.execute_func = Executor::execute_JAL;
            inst_type = InstType::J;
            break;
            
        case Opcode::JALR:
            if (funct3 != 0b000)
                break;
            d_cell.tmp_inst_I.name = InstName::JALR;
            d_cell.tmp_inst_I.execute_func = Executor::execute_JALR;
            inst_type = InstType::I;
            break;

        case Opcode::BRANCH:
            switch (funct3) {
                case 0b000:
                    d_cell.tmp_inst_B.name = InstName::BEQ;
                    d_cell.tmp_inst_B.execute_func = Executor::execute_BEQ;
                    break;

                case 0b001:
                    d_cell.tmp_inst_B.name = InstName::BNE;
                    d_cell.tmp_inst_B.execute_func = Executor::execute_BNE;
                    break;

                case 0b100:
                    d_cell.tmp_inst_B.name = InstName::BLT;
                    d_cell.tmp_inst_B.execute_func = Executor::execute_BLT;
                    break;

                case 0b101:
                    d_cell.tmp_inst_B.name = InstName::BGE;
                    d_cell.tmp_inst_B.execute_func = Executor::execute_BGE;
                    break;

                case 0b110:
                    d_cell.tmp_inst_B.name = InstName::BLTU;
                    d_cell.tmp_inst_B.execute_func = Executor::execute_BLTU;
                    break;

                case 0b111:
                    d_cell.tmp_inst_B.name = InstName::BGEU;
                    d_cell.tmp_inst_B.execute_func = Executor::execute_BGEU;
                    break;

                default:
                    break;
            }
            inst_type = InstType::B;
            break;
    
        case Opcode::LOAD:
            switch (funct3) {
                case 0b000:
                    d_cell.tmp_inst_I.name = InstName::LB;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LB;
                    break;

                case 0b001:
                    d_cell.tmp_inst_I.name = InstName::LH;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LH;
                    break;

                case 0b010:
                    d_cell.tmp_inst_I.name = InstName::LW;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LW;
                    break;

                case 0b100:
                    d_cell.tmp_inst_I.name = InstName::LBU;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LBU;
                    break;

                case 0b101:
                    d_cell.tmp_inst_I.name = InstName::LHU;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LHU;
                    break;

                case 0b110:
                    d_cell.tmp_inst_I.name = InstName::LWU;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LWU;
                    break;

                case 0b011:
                    d_cell.tmp_inst_I.name = InstName::LD;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_LD;
                    break;

                default:
                    break;
            }
            inst_type = InstType::I;
            break;

        case Opcode::STORE:
            switch (funct3) {
                case 0b000:
                    d_cell.tmp_inst_S.name = InstName::SB;
                    d_cell.tmp_inst_S.execute_func = Executor::execute_SB;
                    break;

                case 0b001:
                    d_cell.tmp_inst_S.name = InstName::SH;
                    d_cell.tmp_inst_S.execute_func = Executor::execute_SH;
                    break;

                case 0b010:
                    d_cell.tmp_inst_S.name = InstName::SW;
                    d_cell.tmp_inst_S.execute_func = Executor::execute_SW;
                    break;
                
                case 0b011:
                    d_cell.tmp_inst_S.name = InstName::SD;
                    d_cell.tmp_inst_S.execute_func = Executor::execute_SD;
                    break;

                default:
                    break;
            }
            inst_type = InstType::S;
            break;
             
        case Opcode::OP_IMM:
            switch (funct3) {
                case 0b000:
                    d_cell.tmp_inst_I.name = InstName::ADDI;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_ADDI;
                    break;

                case 0b010:
                    d_cell.tmp_inst_I.name = InstName::SLTI;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_SLTI;
                    break;

                case 0b011:
                    d_cell.tmp_inst_I.name = InstName::SLTIU;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_SLTIU;
                    break;

                case 0b100:
                    d_cell.tmp_inst_I.name = InstName::XORI;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_XORI;
                    break;

                case 0b110:
                    d_cell.tmp_inst_I.name = InstName::ORI;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_ORI;
                    break;

                case 0b111:
                    d_cell.tmp_inst_I.name = InstName::ANDI;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_ANDI;
                    break;
                
                case 0b001:
                    if (funct7 >> 1 != 0b000000)
                        break;
                    d_cell.tmp_inst_I.name = InstName::SLLI;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_SLLI;
                    break;
                
                case 0b101:
                    switch (funct7 >> 1) {
                        case 0b000000:
                            d_cell.tmp_inst_I.name = InstName::SRLI;
                            d_cell.tmp_inst_I.execute_func = Executor::execute_SRLI;
                            break;

                        case 0b010000:
                            d_cell.tmp_inst_I.name = InstName::SRAI;
                            d_cell.tmp_inst_I.execute_func = Executor::execute_SRAI;
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            inst_type = InstType::I;
            break;

        case Opcode::OP:
            switch (funct3) {
                case 0b000:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::ADD;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_ADD;
                            break;

                        case 0b0100000:
                            d_cell.tmp_inst_R.name = InstName::SUB;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SUB;
                            break;

                        default:
                            break;
                    }
                    break;
                
                case 0b001:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::SLL;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SLL;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                
                case 0b010:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::SLT;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SLT;
                            break;
                        
                        default:
                            break;
                    }
                    break;

                case 0b011:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::SLTU;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SLTU;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                
                case 0b100:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::XOR;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_XOR;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                
                case 0b101:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::SRL;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SRL;
                            break;

                        case 0b0100000:
                            d_cell.tmp_inst_R.name = InstName::SRA;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SRA;
                            break;

                        default:
                            break;
                    }
                    break;
                
                case 0b110:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::OR;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_OR;
                            break;

                        default:
                            break;
                    }
                    break;
                
                case 0b111:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::AND;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_AND;
                            break;
                        
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            inst_type = InstType::R;
            break;

        case Opcode::MISC_MEM:
            if (funct3 != 0b000)
                break;

            switch (inst) {
                case 0b10000011001100000000000000001111:
                    d_cell.tmp_inst_I.name = InstName::FENCE_TSO;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_FENCE_TSO;
                    break;
                
                case 0b00000001000000000000000000001111:
                    d_cell.tmp_inst_I.name = InstName::PAUSE;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_PAUSE;  
                    break;        

                default:
                    d_cell.tmp_inst_I.name = InstName::FENCE;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_FENCE;
            }
            inst_type = InstType::I;
            break;

        case Opcode::SYSTEM:
            switch (inst) {
                case 0b00000000000000000000000001110011:
                    d_cell.tmp_inst_I.name = InstName::ECALL;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_ECALL;
                    break;
                
                case 0b00000000000100000000000001110011:
                    d_cell.tmp_inst_I.name = InstName::EBREAK;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_EBREAK;  
                    break;     

                default:
                    break;
            }
            inst_type = InstType::I;
            break;

        case Opcode::OP_IMM_32:
            switch (funct3) {
                case 0b000:
                    d_cell.tmp_inst_I.name = InstName::ADDIW;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_ADDIW;
                    break;
                
                case 0b001:
                    if (funct7 != 0b0000000)
                        break;
                    d_cell.tmp_inst_I.name = InstName::SLLIW;
                    d_cell.tmp_inst_I.execute_func = Executor::execute_SLLIW;
                    break;
                
                case 0b101:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_I.name = InstName::SRLIW;
                            d_cell.tmp_inst_I.execute_func = Executor::execute_SRLIW;
                            break;
                        
                        case 0b0100000:
                            d_cell.tmp_inst_I.name = InstName::SRAIW;
                            d_cell.tmp_inst_I.execute_func = Executor::execute_SRAIW;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                
                default:
                    break;
            }
            inst_type = InstType::I;
            break;

        case Opcode::OP_32:
            switch (funct3) {
                case 0b000:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::ADDW;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_ADDW;
                            break;
                        
                        case 0b0100000:
                            d_cell.tmp_inst_R.name = InstName::SUBW;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SUBW;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                
                case 0b001:
                    if (funct7 != 0b0000000)
                        break;
                    d_cell.tmp_inst_R.name = InstName::SLLW;
                    d_cell.tmp_inst_R.execute_func = Executor::execute_SLLW;
                    break;
                
                case 0b101:
                    switch (funct7) {
                        case 0b0000000:
                            d_cell.tmp_inst_R.name = InstName::SRLW;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SRLW;
                            break;
                        
                        case 0b0100000:
                            d_cell.tmp_inst_R.name = InstName::SRAW;
                            d_cell.tmp_inst_R.execute_func = Executor::execute_SRAW;
                            break;

                        default:
                            break;
                    }
                    break;
                
                default:
                    break;
            }
            inst_type = InstType::R;
            break;

        default:
            break;
    }

    switch (inst_type) {
        case InstType::R:
            d_cell.tmp_inst_R.type   = InstType::R;
            d_cell.tmp_inst_R.rs2    = decode_rs2 (inst);
            d_cell.tmp_inst_R.rs1    = decode_rs1 (inst);
            d_cell.tmp_inst_R.rd     = decode_rd (inst);
            break;
        
        case InstType::I:
            d_cell.tmp_inst_I.type   = InstType::I;
            d_cell.tmp_inst_I.imm    = decode_imm_I (inst);
            d_cell.tmp_inst_I.rs1    = decode_rs1 (inst);
            d_cell.tmp_inst_I.rd     = decode_rd (inst);
            break;
        
        case InstType::S:
            d_cell.tmp_inst_S.type   = InstType::S;
            d_cell.tmp_inst_S.imm    = decode_imm_S (inst);
            d_cell.tmp_inst_S.rs2    = decode_rs2 (inst);
            d_cell.tmp_inst_S.rs1    = decode_rs1 (inst);
            break;
        
        case InstType::B:
            d_cell.tmp_inst_B.type   = InstType::B;
            d_cell.tmp_inst_B.imm    = decode_imm_B (inst);
            d_cell.tmp_inst_B.rs2    = decode_rs2 (inst);
            d_cell.tmp_inst_B.rs1    = decode_rs1 (inst);
            break;
        
        case InstType::U:
            d_cell.tmp_inst_U.type   = InstType::U;
            d_cell.tmp_inst_U.imm    = decode_imm_U (inst);
            d_cell.tmp_inst_U.rd     = decode_rd (inst);
            break;
        
        case InstType::J:
            d_cell.tmp_inst_J.type   = InstType::J;
            d_cell.tmp_inst_J.imm    = decode_imm_J (inst);
            d_cell.tmp_inst_J.rd     = decode_rd (inst);
            break;
    }

    return inst_type;
}