#include "cpu/exec/template-start.h"

#define instr jcc

static void do_execute() {
    // 检查条件是否满足
    bool condition = false;
    
    // 根据不同的指令设置不同的条件
    #if defined(instr_jz) || defined(instr_je)
        condition = cpu.eflags.ZF;
    #elif defined(instr_jnz) || defined(instr_jne)
        condition = !cpu.eflags.ZF;
    #elif defined(instr_jg) || defined(instr_jnle)
        condition = !cpu.eflags.ZF && (cpu.eflags.SF == cpu.eflags.OF);
    #elif defined(instr_jl) || defined(instr_jnge)
        condition = (cpu.eflags.SF != cpu.eflags.OF);
    #elif defined(instr_jge) || defined(instr_jnl)
        condition = (cpu.eflags.SF == cpu.eflags.OF);
    #elif defined(instr_jle) || defined(instr_jng)
        condition = cpu.eflags.ZF || (cpu.eflags.SF != cpu.eflags.OF);
    #elif defined(instr_ja) || defined(instr_jnbe)
        condition = !cpu.eflags.CF && !cpu.eflags.ZF;
    #elif defined(instr_jb) || defined(instr_jnae) || defined(instr_jc)
        condition = cpu.eflags.CF;
    #elif defined(instr_jae) || defined(instr_jnb) || defined(instr_jnc)
        condition = !cpu.eflags.CF;
    #elif defined(instr_jbe) || defined(instr_jna)
        condition = cpu.eflags.CF || cpu.eflags.ZF;
    #endif
    
    // 如果条件满足，则跳转到目标地址
    if (condition) {
        cpu.eip += op_src->val;
    }
    
    print_asm(str(instr) " %x", cpu.eip + 1 + DATA_BYTE);
}

make_instr_helper(si)

#if DATA_BYTE == 1 || DATA_BYTE == 4
/* sign immediate */
make_helper(concat(decode_si_, SUFFIX)) {
    op_src->type = OP_TYPE_IMM;
    
    /* 读取DATA_BYTE字节的内存，并将其解释为有符号立即数 */
    uint32_t imm = instr_fetch(eip, DATA_BYTE);
    if (DATA_BYTE == 1) {
        op_src->simm = (int8_t)imm;
    } else {
        op_src->simm = (int32_t)imm;
    }
    
    op_src->val = op_src->simm;

#ifdef DEBUG
    snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->val);
#endif
    return DATA_BYTE;
}
#endif

#include "cpu/exec/template-end.h"