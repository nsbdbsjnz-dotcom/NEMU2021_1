#include "cpu/exec/template-start.h"

#define instr dec

static void do_execute () {
	DATA_TYPE result = op_src->val - 1;
	OPERAND_W(op_src, result);

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

	cpu.eflags.OF = (result == 0x7fffffff);

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"