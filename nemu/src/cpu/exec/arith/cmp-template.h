#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute () {
	DATA_TYPE result = op_dest->val - op_src->val;

	// PF (Parity Flag): 奇偶标志 (低8位中1的个数为偶数)
	int val = result & 0xff;
	val ^= val >> 4;
	val ^= val >> 2;
	val ^= val >> 1;
	cpu.eflags.PF = (~val) & 1;

	// ZF (Zero Flag): 零标志
	cpu.eflags.ZF = (result == 0);

	// SF (Sign Flag): 符号标志
	cpu.eflags.SF = MSB(result);

	cpu.eflags.CF = result > op_dest->val;
	cpu.eflags.OF = MSB((op_dest->val ^ op_src->val) & (op_dest->val ^ result));

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"