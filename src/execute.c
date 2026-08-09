#include "execute.h"
#include "memory.h"
#include "decoder.h"


void execute(struct CPU *cpu, uint32_t inst){
    struct INST c_instruction;
    decode(inst, &c_instruction);

    switch (c_instruction.type){
    case R_Type:
        switch (c_instruction.funct3){
        case 0x0:
            if(c_instruction.funct7 == 0x0){
                uint32_t add = get_reg(cpu, c_instruction.rs1) + get_reg(cpu, c_instruction.rs2);
                write_reg(cpu, add , c_instruction.rd);
            } else if(c_instruction.funct7 == 0x20){
                uint32_t sub = get_reg(cpu, c_instruction.rs1) - get_reg(cpu, c_instruction.rs2);
                write_reg(cpu, sub, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;
        
        case 0x4:
            if(c_instruction.funct7 == 0x00){
                uint32_t xor = get_reg(cpu, c_instruction.rs1) ^ get_reg(cpu, c_instruction.rs2);        
                write_reg(cpu, xor, c_instruction.rd);        
            } else{
                ill_inst();
            }
            break;

        case 0x6:
            if(c_instruction.funct7 == 0x00){
                uint32_t or = get_reg(cpu, c_instruction.rs1) | get_reg(cpu, c_instruction.rs2);
                write_reg(cpu, or, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;

        case 0x7:
            if(c_instruction.funct7 == 0x00){
                uint32_t and = get_reg(cpu, c_instruction.rs1) & get_reg(cpu, c_instruction.rs2);
                write_reg(cpu, and, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;

        case 0x1:
            if(c_instruction.funct7 == 0x00){
                uint32_t sll = get_reg(cpu, c_instruction.rs1) << (get_reg(cpu, c_instruction.rs2) & 0x1F);
                write_reg(cpu, sll, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;

        case 0x5:
            if(c_instruction.funct7 == 0x00){
                uint32_t srl = get_reg(cpu, c_instruction.rs1) >> (get_reg(cpu, c_instruction.rs2) & 0x1F);
                write_reg(cpu, srl, c_instruction.rd);
            } else if(c_instruction.funct7 == 0x20){
                uint32_t sra = (int32_t)get_reg(cpu, c_instruction.rs1) >> (get_reg(cpu, c_instruction.rs2) & 0x1F);
                write_reg(cpu, sra, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;

        case 0x2:
            if(c_instruction.funct7 == 0x00){
                int32_t slt = ((int32_t)get_reg(cpu, c_instruction.rs1) < (int32_t)get_reg(cpu, c_instruction.rs2)) ? 1 : 0;
                write_reg(cpu, slt, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;

        case 0x3:
            if(c_instruction.funct7 == 0x00){
                uint32_t sltu = (get_reg(cpu, c_instruction.rs1) < get_reg(cpu, c_instruction.rs2)) ? 1 : 0;
                write_reg(cpu, sltu, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;

        default:
            ill_inst();
            break;
        }
        break;

    case I_Type:
        switch (c_instruction.funct3)
        {
        case 0x0:
            uint32_t addi = get_reg(cpu, c_instruction.rs1) + c_instruction.imm;
            write_reg(cpu, addi, c_instruction.rd);
            break;
        
        case 0x4:
            uint32_t xori = get_reg(cpu, c_instruction.rs1) ^ c_instruction.imm;
            write_reg(cpu, xori, c_instruction.rd);
            break;
                    
        case 0x6:
            uint32_t ori = get_reg(cpu, c_instruction.rs1) | c_instruction.imm;
            write_reg(cpu, ori, c_instruction.rd);
            break;
                
        case 0x7:
            uint32_t andi = get_reg(cpu, c_instruction.rs1) & c_instruction.imm;
            write_reg(cpu, andi, c_instruction.rd);
            break;
                    
        case 0x1:
            if(((c_instruction.imm >> 5) & 0x7F) == 0x00){
            uint32_t slli = get_reg(cpu, c_instruction.rs1) << (c_instruction.imm & 0x1F);
            write_reg(cpu, slli, c_instruction.rd);
            } else{
                ill_inst();
            }
            break;
                            
        case 0x5:
            if(((c_instruction.imm >> 5) & 0x7F) == 0x00){
            uint32_t srli = get_reg(cpu, c_instruction.rs1) >> (c_instruction.imm & 0x1F);
            write_reg(cpu, srli, c_instruction.rd);
            } else if(((c_instruction.imm >> 5) & 0x7F) == 0x20){
            uint32_t srai = (int32_t)get_reg(cpu, c_instruction.rs1) >> (c_instruction.imm & 0x1F);
            write_reg(cpu, srai, c_instruction.rd);                
            } else{
                ill_inst();
            }
            break;
                    
        case 0x2:
            uint32_t slti = ((int32_t)get_reg(cpu, c_instruction.rs1) < (int32_t)c_instruction.imm) ? 1 : 0;
            write_reg(cpu, slti, c_instruction.rd);
            break;    

        case 0x3:
            uint32_t sltiu = (get_reg(cpu, c_instruction.rs1) < c_instruction.imm) ? 1 : 0;
            write_reg(cpu, sltiu, c_instruction.rd);
            break;

        default:
            ill_inst();
            break;
        }
        break;
    
    default:
        ill_inst();
        break;
    }
}
