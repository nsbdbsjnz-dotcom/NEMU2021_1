#include "cpu/exec/template-start.h"

#define instr add

static void do_execute() {
    // 1. 执行加法
    // DATA_TYPE 会根据编译情况自动变成 uint8_t, uint16_t 或 uint32_t
    DATA_TYPE src = op_src->val;
    DATA_TYPE dest = op_dest->val;
    DATA_TYPE result = dest + src;

    // 2. 写回结果
    OPERAND_W(op_dest, result);

    // 3. 更新 EFLAGS (移植你刚才的逻辑)
    // ---------------------------------------------------------
    
    // CF (Carry Flag): 进位标志
    // 在无符号加法中，如果结果比任何一个加数小，说明溢出了
    cpu.eflags.CF = result < dest;

    // PF (Parity Flag): 奇偶标志 (低8位中1的个数为偶数)
    // 利用简单的异或折叠算法
    int val = result & 0xff;
    val ^= val >> 4;
    val ^= val >> 2;
    val ^= val >> 1;
    cpu.eflags.PF = (~val) & 1;

    // ZF (Zero Flag): 零标志
    cpu.eflags.ZF = (result == 0);

    // SF (Sign Flag): 符号标志
    // MSB 宏在这里是可以正常使用的！会自动取最高位。
    cpu.eflags.SF = MSB(result);

    // OF (Overflow Flag): 溢出标志 (针对有符号数)
    // 只有当“正+正=负”或者“负+负=正”时，OF=1
    int dest_sign = MSB(dest);
    int src_sign = MSB(src);
    int res_sign = MSB(result);
    cpu.eflags.OF = (dest_sign == src_sign) && (res_sign != dest_sign);

    // ---------------------------------------------------------

    print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
#undef instr