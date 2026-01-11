#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
    // 添加调试输出
    printf("DEBUG: jmp_si_%s called\n", str(SUFFIX));
    printf("DEBUG: Current eip = 0x%08x\n", cpu.eip);
    printf("DEBUG: Jump offset = 0x%08x\n", op_src->val);
    
    // For direct jumps, op_src->val is the offset from the next instruction
    // So we need to calculate the correct target address
    cpu.eip = op_src->val;
    printf("DEBUG: New eip = 0x%08x\n", cpu.eip);
    
    print_asm(str(instr) " %x", cpu.eip + DATA_BYTE + 1);
}

make_instr_helper(si)
#if DATA_BYTE == 4
make_helper(jmp_rm_l) {
    int len = decode_rm_l(eip + 1);
    
    // 添加调试输出
    printf("DEBUG: jmp_rm_l called\n");
    printf("DEBUG: Current eip = 0x%08x\n", cpu.eip);
    printf("DEBUG: Jump target = 0x%08x\n", op_src->val);
    
    cpu.eip = op_src->val;
    printf("DEBUG: New eip = 0x%08x\n", cpu.eip);
    
    print_asm(str(instr) " *%s", op_src->str);
    return len + 1;
}
#endif
#include "cpu/exec/template-end.h"