#include "cpu/exec/template-start.h"

// 定义一个宏来统一处理跳转逻辑
// cond 是跳转条件，例如 cpu.eflags.ZF == 1
#define make_jcc_helper(cond) \
    if (cond) { \
        /* op_src->val 是指令中解码出的立即数偏移量 (已经符号扩展) */ \
        /* 这里直接加到 eip 上，配合主循环的 eip += len，最终结果就是 eip + len + offset */ \
        cpu.eip += op_src->val; \
        \
        /* 如果是 16 位模式，需要对 EIP 进行截断处理 */ \
        if (DATA_BYTE == 2) { \
            cpu.eip &= 0x0000FFFF; \
        } \
    } \
    print_asm_template2();

/* --- 以下是各种条件跳转指令的定义 --- */

// 1. JE / JZ: 结果为0 (Equal / Zero)
#define instr je
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 1); }
make_instr_helper(si)
#undef instr

#define instr jz
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 1); }
make_instr_helper(si)
#undef instr

// 2. JNE / JNZ: 结果不为0 (Not Equal / Not Zero)
#define instr jne
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 0); }
make_instr_helper(si)
#undef instr

#define instr jnz
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 0); }
make_instr_helper(si)
#undef instr

// 3. JS: 结果为负 (Sign)
#define instr js
static void do_execute() { make_jcc_helper(cpu.eflags.SF == 1); }
make_instr_helper(si)
#undef instr

// 4. JNS: 结果非负 (No Sign)
#define instr jns
static void do_execute() { make_jcc_helper(cpu.eflags.SF == 0); }
make_instr_helper(si)
#undef instr

// 5. JG: 有符号 > (Greater) -> ZF=0 且 SF=OF
#define instr jg
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 0 && cpu.eflags.SF == cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// 6. JGE: 有符号 >= (Greater or Equal) -> SF=OF
#define instr jge
static void do_execute() { make_jcc_helper(cpu.eflags.SF == cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// 7. JL: 有符号 < (Less) -> SF != OF
#define instr jl
static void do_execute() { make_jcc_helper(cpu.eflags.SF != cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// 8. JLE: 有符号 <= (Less or Equal) -> ZF=1 或 SF!=OF
#define instr jle
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 1 || cpu.eflags.SF != cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// 9. JA: 无符号 > (Above) -> CF=0 且 ZF=0
#define instr ja
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 0 && cpu.eflags.ZF == 0); }
make_instr_helper(si)
#undef instr

// 10. JAE: 无符号 >= (Above or Equal) -> CF=0
#define instr jae
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 0); }
make_instr_helper(si)
#undef instr

// 11. JB: 无符号 < (Below) -> CF=1
#define instr jb
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 1); }
make_instr_helper(si)
#undef instr

// 12. JBE: 无符号 <= (Below or Equal) -> CF=1 或 ZF=1
#define instr jbe
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 1 || cpu.eflags.ZF == 1); }
make_instr_helper(si)
#undef instr
// 13. JP / JPE: 奇偶位为1 (Parity / Parity Even)
#define instr jp
static void do_execute() { make_jcc_helper(cpu.eflags.PF == 1); }
make_instr_helper(si)
#undef instr

// 14. JNP / JPO: 奇偶位为0 (No Parity / Parity Odd)
#define instr jnp
static void do_execute() { make_jcc_helper(cpu.eflags.PF == 0); }
make_instr_helper(si)
#undef instr

// 15. JO: 溢出 (Overflow)
#define instr jo
static void do_execute() { make_jcc_helper(cpu.eflags.OF == 1); }
make_instr_helper(si)
#undef instr

// 16. JNO: 未溢出 (No Overflow)
#define instr jno
static void do_execute() { make_jcc_helper(cpu.eflags.OF == 0); }
make_instr_helper(si)
#undef instr
#include "cpu/exec/template-end.h"