#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
    // For direct jumps, op_src->val is the offset from the next instruction
    // So we need to calculate the correct target address
    cpu.eip = op_src->val;
    print_asm(str(instr) " %x", cpu.eip + DATA_BYTE + 1);
}

make_instr_helper(si)
#if DATA_BYTE == 4
make_helper(jmp_rm_l) {
    int len = decode_rm_l(eip + 1);
    cpu.eip = op_src->val;
    print_asm(str(instr) " *%s", op_src->str);
    return len + 1;
}
#endif
#include "cpu/exec/template-end.h"