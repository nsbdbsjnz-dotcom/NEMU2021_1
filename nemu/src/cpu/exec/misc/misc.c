#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(nop) {
	print_asm("nop");
	return 1;
}

make_helper(int3) {
	void do_int3();
	do_int3();
	print_asm("int3");

	return 1;
}

make_helper(lea) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = load_addr(eip + 1, &m, op_src);
	reg_l(m.reg) = op_src->addr;

	print_asm("leal %s,%%%s", op_src->str, regsl[m.reg]);
	return 1 + len;
}
/* Temporary stubs for PA3 instructions to fix compilation errors */
make_helper(lgdt) {
    // 暂时没实现，PA3再写
    return 0; 
}

make_helper(mov_cr2rm) {
    return 0;
}

make_helper(mov_rm2cr) {
    return 0;
}

make_helper(mov_rm2sreg) {
    return 0;
}