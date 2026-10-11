#include "execute.h"
#include "memory.h"
#include "decoder.h"


void execute(struct CPU *cpu, uint32_t inst){
    uint32_t next_pc = cpu->pc + 4;

    struct INST c_instruction;
    decode(inst, &c_instruction);

    switch (c_instruction.opcode){
    case 0x33:
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

    case 0x13:
        switch (c_instruction.funct3){
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
    
    case 0x03:
        switch (c_instruction.funct3){
        case 0x0: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            int8_t data = read_byte(cpu, addr);
            write_reg(cpu, (int32_t)data, c_instruction.rd);
            break;
        }

        case 0x1: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            int16_t data = read_half(cpu, addr);
            write_reg(cpu, (int32_t)data, c_instruction.rd);
            break;
        }

        case 0x2: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            uint32_t data = read_word(cpu, addr);
            write_reg(cpu, data, c_instruction.rd);
            break;
        }

        case 0x4: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            uint32_t data = read_byte(cpu, addr);
            write_reg(cpu, data, c_instruction.rd);
            break;
        }

        case 0x5: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            uint16_t data = read_half(cpu, addr);
            write_reg(cpu, data, c_instruction.rd);
            break;
        }

        default:
            ill_inst();
            break;
        }
        
        break;

    case 0x23:
        switch (c_instruction.funct3){
        case 0x0: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            uint8_t data = (get_reg(cpu, c_instruction.rs2) & (0xFF));
            write_byte(cpu, addr, data);
            break;
        }

        case 0x1: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            uint32_t data = (get_reg(cpu, c_instruction.rs2) & 0xFFFF);
            write_byte(cpu, addr, data & 0xFF);
            write_byte(cpu, addr + 1, (data >> 8) & 0xFF);
            break;

        }

        case 0x2: {
            uint32_t addr = (get_reg(cpu, c_instruction.rs1) + c_instruction.imm);
            uint32_t data = (get_reg(cpu, c_instruction.rs2));
            write_word(cpu, addr, data);
            break;
        }

        default:
            break;
        }
    
        break;
    case 0x63: {
        uint32_t rs1 = get_reg(cpu, c_instruction.rs1);
        uint32_t rs2 = get_reg(cpu, c_instruction.rs2);
        uint8_t taken = 0;

        switch (c_instruction.funct3){
        case 0x0:
            taken = (rs1 == rs2);
            break;

        case 0x1:
            taken = (rs1 != rs2);
            break;

        case 0x4:
            taken = ((int32_t)rs1 < (int32_t)rs2);
            break;

        case 0x5:
            taken = ((int32_t)rs1 >= (int32_t)rs2);
            break;

        case 0x6:
            taken = (rs1 < rs2);
            break;

        case 0x7:
            taken = (rs1 >= rs2);
            break;

        default:
            ill_inst();
            break;
        }

        if(taken){
            next_pc = cpu->pc + c_instruction.imm;
        }

        break;
    }

    default:
        ill_inst();
        break;
    }

    cpu->pc = next_pc;
}
