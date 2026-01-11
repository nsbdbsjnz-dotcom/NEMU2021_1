#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
    // For direct jumps, op_src->val is the offset from the next instruction
    // So we need to calculate the correct target address
    // The next instruction address is eip + len + 1, where len is the length of the offset
    // So the target address is (eip + len + 1) + op_src->val
    // But in the idex function, execute() is called before returning len + 1
    // So we need to get the current eip and add the offset to it
    cpu.eip += op_src->val;
    print_asm(str(instr) " %x", cpu.eip + 1);
}

make_instr_helper(si)
#if DATA_BYTE == 4
make_helper(jmp_rm_l) {
    int len = decode_rm_l(eip + 1);
    cpu.eip = op_src->val - (len + 1);
    print_asm(str(instr) " *%s", op_src->str);
    return len + 1;
}
#endif
#include "cpu/exec/template-end.h"