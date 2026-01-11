#include "cpu/exec/template-start.h"

// 统一跳转宏：符合条件则修改EIP
#define make_jcc_helper(cond) \
    if (cond) { \
        cpu.eip += op_src->val; \
        if (DATA_BYTE == 2) cpu.eip &= 0x0000FFFF; \
    } \
    print_asm_template2();

/* --- 核心指令实现 --- */

// JE / JZ: Equal / Zero (ZF=1)
#define instr je
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 1); }
make_instr_helper(si)
#undef instr

#define instr jz
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 1); }
make_instr_helper(si)
#undef instr

// JNE / JNZ: Not Equal / Not Zero (ZF=0)
#define instr jne
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 0); }
make_instr_helper(si)
#undef instr

#define instr jnz
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 0); }
make_instr_helper(si)
#undef instr

// JS: Sign (SF=1)
#define instr js
static void do_execute() { make_jcc_helper(cpu.eflags.SF == 1); }
make_instr_helper(si)
#undef instr

// JNS: No Sign (SF=0)
#define instr jns
static void do_execute() { make_jcc_helper(cpu.eflags.SF == 0); }
make_instr_helper(si)
#undef instr

/* === 重点检查这里 === */
// JG: Greater (有符号 >) -> ZF=0 且 SF=OF
// 这里的 helper 必须是 si (signed immediate)，绝对不能是 r
#define instr jg
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 0 && cpu.eflags.SF == cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// JGE: Greater or Equal (有符号 >=) -> SF=OF
#define instr jge
static void do_execute() { make_jcc_helper(cpu.eflags.SF == cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// JL: Less (有符号 <) -> SF != OF
#define instr jl
static void do_execute() { make_jcc_helper(cpu.eflags.SF != cpu.eflags.OF); }
make_instr_helper(si)
#undef instr

// JLE: Less or Equal (有符号 <=) -> ZF=1 或 SF!=OF
#define instr jle
static void do_execute() { make_jcc_helper(cpu.eflags.ZF == 1 || cpu.eflags.SF != cpu.eflags.OF); }
make_instr_helper(si)
#undef instr
/* =================== */

// JA: Above (无符号 >) -> CF=0 且 ZF=0
#define instr ja
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 0 && cpu.eflags.ZF == 0); }
make_instr_helper(si)
#undef instr

// JAE: Above or Equal (无符号 >=) -> CF=0
#define instr jae
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 0); }
make_instr_helper(si)
#undef instr

// JB: Below (无符号 <) -> CF=1
#define instr jb
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 1); }
make_instr_helper(si)
#undef instr

// JBE: Below or Equal (无符号 <=) -> CF=1 或 ZF=1
#define instr jbe
static void do_execute() { make_jcc_helper(cpu.eflags.CF == 1 || cpu.eflags.ZF == 1); }
make_instr_helper(si)
#undef instr

// JP: Parity (PF=1)
#define instr jp
static void do_execute() { make_jcc_helper(cpu.eflags.PF == 1); }
make_instr_helper(si)
#undef instr

// JNP: No Parity (PF=0)
#define instr jnp
static void do_execute() { make_jcc_helper(cpu.eflags.PF == 0); }
make_instr_helper(si)
#undef instr

// JO: Overflow (OF=1)
#define instr jo
static void do_execute() { make_jcc_helper(cpu.eflags.OF == 1); }
make_instr_helper(si)
#undef instr

// JNO: No Overflow (OF=0)
#define instr jno
static void do_execute() { make_jcc_helper(cpu.eflags.OF == 0); }
make_instr_helper(si)
#undef instr

#include "cpu/exec/template-end.h"
#undef instr