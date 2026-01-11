#include "cpu/helper.h"
#include "cpu/decode/modrm.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);
static make_helper(_2byte_esc);

#define make_group(name, item0, item1, item2, item3, item4, item5, item6, item7) \
    static helper_fun concat(opcode_table_, name) [8] = { \
    /* 0x00 */  item0, item1, item2, item3, \
    /* 0x04 */  item4, item5, item6, item7  \
    }; \
    static make_helper(name) { \
        ModR_M m; \
        m.val = instr_fetch(eip + 1, 1); \
        return concat(opcode_table_, name) [m.opcode](eip); \
    }
    
/* 0x80 - 0xd3 的 group 保持不变... */
make_group(group1_b, inv, inv, inv, inv, and_i2rm_b, inv, inv, inv)
make_group(group1_v, inv, inv, inv, inv, and_i2rm_v, sub_i2rm_v, inv, inv)
make_group(group1_sx_v, inv, or_si2rm_v, inv, inv, and_si2rm_v, sub_si2rm_v, inv, inv)
make_group(group2_i_b, inv, inv, inv, inv, inv, inv, inv, inv)
make_group(group2_i_v, inv, inv, inv, inv, shl_rm_imm_v, shr_rm_imm_v, inv, sar_rm_imm_v)
make_group(group2_1_b, inv, inv, inv, inv, inv, inv, inv, inv)
make_group(group2_1_v, inv, inv, inv, inv, inv, inv, inv, sar_rm_1_v)
make_group(group2_cl_b, inv, inv, inv, inv, inv, inv, inv, inv)
make_group(group2_cl_v, inv, inv, inv, inv, shl_rm_cl_v, inv, inv, inv)
make_group(group3_b, inv, inv, inv, inv, inv, inv, inv, inv)
make_group(group3_v, inv, inv, not_rm_v, neg_rm_v, mul_rm_v, imul_rm2a_v, div_rm_v, idiv_rm_v)
make_group(group4, inv, inv, inv, inv, inv, inv, inv, inv)
make_group(group5, inv, dec_rm_v, inv, inv, jmp_rm_l, inv, inv, inv)
make_group(group6, inv, inv, inv, inv, inv, inv, inv, inv)

/* ========================================================================
 * --- PA3 新增部分 开始：修改 group7 以注册 lgdt --- 
 * ======================================================================== */
/* 根据 i386 手册，lgdt 指令位于 0F 01 /2 (即第2号子操作码) */
make_group(group7,
    inv, inv, lgdt, inv, 
    inv, inv, inv, inv)
/* ========================================================================
 * --- PA3 新增部分 结束 --- 
 * ======================================================================== */

helper_fun opcode_table [256] = {
/* 0x00 */  inv, inv, inv, inv,
/* 0x04 */  inv, inv, inv, inv,
/* 0x08 */  inv, or_r2rm_v, or_rm2r_b, inv,
/* 0x0c */  or_i2a_b, inv, inv, _2byte_esc,
/* 0x10 - 0x88 保持不变... */
/* 0x10 */  inv, adc_r2rm_v, inv, inv,
/* 0x14 */  inv, inv, inv, inv,
/* 0x18 */  inv, sbb_r2rm_v, inv, inv,
/* 0x1c */  inv, inv, inv, inv,
/* 0x20 */  inv, and_r2rm_v, and_rm2r_b, inv,
/* 0x24 */  inv, inv, inv, inv,
/* 0x28 */  inv, sub_r2rm_v, inv, sub_rm2r_v,
/* 0x2c */  inv, inv, inv, inv,
/* 0x30 */  inv, xor_r2rm_v, inv, inv,
/* 0x34 */  inv, inv, inv, inv,
/* 0x38 */  inv, inv, inv, inv,
/* 0x3c */  inv, inv, inv, inv,
/* 0x40 */  inc_r_v, inc_r_v, inc_r_v, inc_r_v,
/* 0x44 */  inv, inc_r_v, inc_r_v, inc_r_v,
/* 0x48 */  dec_r_v, dec_r_v, dec_r_v, dec_r_v,
/* 0x4c */  inv, dec_r_v, dec_r_v, dec_r_v,
/* 0x50 */  inv, inv, inv, inv,
/* 0x54 */  inv, inv, inv, inv,
/* 0x58 */  inv, inv, inv, inv,
/* 0x5c */  inv, inv, inv, inv, 
/* 0x60 */  inv, inv, inv, inv,
/* 0x64 */  inv, inv, operand_size, inv,
/* 0x68 */  inv, imul_i_rm2r_v, inv, imul_si_rm2r_v,
/* 0x6c */  inv, inv, inv, inv,
/* 0x70 */  inv, inv, inv, inv,
/* 0x74 */  inv, inv, inv, inv,
/* 0x78 */  inv, inv, inv, inv,
/* 0x7c */  inv, inv, inv, inv,
/* 0x80 */  group1_b, group1_v, inv, group1_sx_v, 
/* 0x84 */  inv, inv, inv, inv,
/* 0x88 */  mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,

/* ========================================================================
 * --- PA3 新增部分 开始：注册 mov_rm2sreg (0x8E) --- 
 * ======================================================================== */
/* 0x8c */  inv, lea, mov_rm2sreg, inv,
/* ========================================================================
 * --- PA3 新增部分 结束 --- 
 * ======================================================================== */

/* 0x90 - 0xff 保持不变... */
/* 0x90 */  nop, inv, inv, inv,
/* 0x94 */  inv, inv, inv, inv,
/* 0x98 */  inv, cltd_v, inv, inv,
/* 0x9c */  inv, inv, inv, inv,
/* 0xa0 */  mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */  movs_b, movs_v, inv, inv,
/* 0xa8 */  inv, inv, stos_b, stos_v,
/* 0xac */  inv, inv, scas_b, inv,
/* 0xb0 */  mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */  mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */  mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */  mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */  group2_i_b, group2_i_v, inv, inv,
/* 0xc4 */  inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */  inv, inv, inv, inv,
/* 0xcc */  int3, inv, inv, inv,
/* 0xd0 */  group2_1_b, group2_1_v, group2_cl_b, group2_cl_v,
/* 0xd4 */  inv, inv, nemu_trap, inv,
/* 0xd8 */  inv, inv, inv, inv,
/* 0xdc */  inv, inv, inv, inv,
/* 0xe0 */  inv, inv, inv, inv,
/* 0xe4 */  inv, inv, inv, inv,
/* 0xe8 */  inv, jmp_si_l, inv, jmp_si_b,
/* 0xec */  inv, inv, inv, inv,
/* 0xf0 */  inv, inv, repnz, rep,
/* 0xf4 */  inv, inv, group3_b, group3_v,
/* 0xf8 */  inv, inv, inv, inv,
/* 0xfc */  inv, inv, group4, group5
};

helper_fun _2byte_opcode_table [256] = {
/* 0x00 */  group6, group7, inv, inv, 
/* 0x04 */  inv, inv, inv, inv, 
/* 0x08 - 0x1c 保持不变... */
/* 0x08 */  inv, inv, inv, inv, 
/* 0x0c */  inv, inv, inv, inv, 
/* 0x10 */  inv, inv, inv, inv, 
/* 0x14 */  inv, inv, inv, inv, 
/* 0x18 */  inv, inv, inv, inv, 
/* 0x1c */  inv, inv, inv, inv, 

/* ========================================================================
 * --- PA3 新增部分 开始：注册控制寄存器读写 (0x20, 0x22) --- 
 * ======================================================================== */
/* 0x20 */  mov_cr2rm, inv, mov_rm2cr, inv, 
/* ========================================================================
 * --- PA3 新增部分 结束 --- 
 * ======================================================================== */

/* 其余 2 字节操作码表内容保持不变... */
/* 0x24 - 0xff */
/* 0x24 */  inv, inv, inv, inv,
/* 0x28 */  inv, inv, inv, inv, 
/* 0x2c */  inv, inv, inv, inv, 
/* 0x30 */  inv, inv, inv, inv, 
/* 0x34 */  inv, inv, inv, inv,
/* 0x38 */  inv, inv, inv, inv, 
/* 0x3c */  inv, inv, inv, inv, 
/* 0x40 */  inv, inv, inv, inv, 
/* 0x44 */  inv, inv, inv, inv,
/* 0x48 */  inv, inv, inv, inv, 
/* 0x4c */  inv, inv, inv, inv, 
/* 0x50 */  inv, inv, inv, inv, 
/* 0x54 */  inv, inv, inv, inv,
/* 0x58 */  inv, inv, inv, inv, 
/* 0x5c */  inv, inv, inv, inv, 
/* 0x60 */  inv, inv, inv, inv,
/* 0x64 */  inv, inv, inv, inv,
/* 0x68 */  inv, inv, inv, inv, 
/* 0x6c */  inv, inv, inv, inv, 
/* 0x70 */  jz_si_b, jnz_si_b, jb_si_b, jae_si_b,
/* 0x74 */  jz_si_b, jnz_si_b, jbe_si_b, ja_si_b,
/* 0x78 */  inv, inv, inv, inv, 
/* 0x7c */  inv, inv, jl_si_b, jge_si_b, 
/* 0x80 */  inv, inv, inv, inv,
/* 0x84 */  inv, inv, inv, inv,
/* 0x88 */  inv, inv, inv, inv, 
/* 0x8c */  inv, inv, inv, inv, 
/* 0x90 */  inv, inv, inv, inv,
/* 0x94 */  inv, inv, inv, inv,
/* 0x98 */  inv, inv, inv, inv, 
/* 0x9c */  inv, inv, inv, inv, 
/* 0xa0 */  inv, inv, inv, inv, 
/* 0xa4 */  inv, inv, inv, inv,
/* 0xa8 */  inv, inv, inv, inv,
/* 0xac */  inv, inv, inv, imul_rm2r_v,
/* 0xb0 */  inv, inv, inv, inv, 
/* 0xb4 */  inv, inv, movzb_v, inv, 
/* 0xb8 */  inv, inv, inv, inv,
/* 0xbc */  inv, inv, movsb_v, movsw_l,
/* 0xc0 - 0xff 保持不变... */
/* 0xc0 */  inv, inv, inv, inv,
/* 0xc4 */  inv, inv, inv, inv,
/* 0xc8 */  inv, inv, inv, inv,
/* 0xcc */  inv, inv, inv, inv,
/* 0xd0 */  inv, inv, inv, inv,
/* 0xd4 */  inv, inv, inv, inv,
/* 0xd8 */  inv, inv, inv, inv,
/* 0xdc */  inv, inv, inv, inv,
/* 0xe0 */  inv, inv, inv, inv,
/* 0xe4 */  inv, inv, inv, inv,
/* 0xe8 */  inv, inv, inv, inv,
/* 0xec */  inv, inv, inv, inv,
/* 0xf0 */  inv, inv, inv, inv,
/* 0xf4 */  inv, inv, inv, inv,
/* 0xf8 */  inv, inv, inv, inv,
/* 0xfc */  inv, inv, inv, inv
};

make_helper(exec) {
    ops_decoded.opcode = instr_fetch(eip, 1);
    return opcode_table[ ops_decoded.opcode ](eip);
}

static make_helper(_2byte_esc) {
    eip ++;
    uint32_t opcode = instr_fetch(eip, 1);
    ops_decoded.opcode = opcode | 0x100;
    return _2byte_opcode_table[opcode](eip) + 1; 
}

// 删除从这里开始的所有内容
#ifndef __JCC_H__
#define __JCC_H__

#include "cpu/helper.h"

// 8位条件跳转指令
make_helper(jz_si_b);
make_helper(jnz_si_b);
make_helper(jg_si_b);
make_helper(jl_si_b);
make_helper(jge_si_b);
make_helper(jle_si_b);
make_helper(ja_si_b);
make_helper(jb_si_b);
make_helper(jae_si_b);
make_helper(jbe_si_b);

// 16位条件跳转指令
make_helper(jz_si_w);
make_helper(jnz_si_w);
make_helper(jg_si_w);
make_helper(jl_si_w);
make_helper(jge_si_w);
make_helper(jle_si_w);
make_helper(ja_si_w);
make_helper(jb_si_w);
make_helper(jae_si_w);
make_helper(jbe_si_w);

// 32位条件跳转指令
make_helper(jz_si_l);
make_helper(jnz_si_l);
make_helper(jg_si_l);
make_helper(jl_si_l);
make_helper(jge_si_l);
make_helper(jle_si_l);
make_helper(ja_si_l);
make_helper(jb_si_l);
make_helper(jae_si_l);
make_helper(jbe_si_l);

// 通用条件跳转指令
make_helper(jz_si_v);
make_helper(jnz_si_v);
make_helper(jg_si_v);
make_helper(jl_si_v);
make_helper(jge_si_v);
make_helper(jle_si_v);
make_helper(ja_si_v);
make_helper(jb_si_v);
make_helper(jae_si_v);
make_helper(jbe_si_v);

#endif

// 在opcode_table中添加条件跳转指令的注册
// 条件跳转指令的opcode范围是0x70-0x7f


// 修改opcode_table中的条件跳转指令部分
/* 0x70 */  jz_si_b, jnz_si_b, jb_si_b, jnb_si_b,
/* 0x74 */  je_si_b, jne_si_b, jbe_si_b, ja_si_b,
/* 0x78 */  js_si_b, jns_si_b, jp_si_b, jnp_si_b,
/* 0x7c */  jo_si_b, jno_si_b, jl_si_b, jnl_si_b,