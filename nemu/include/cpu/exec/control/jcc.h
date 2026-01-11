#ifndef __JCC_H__
#define __JCC_H__

#include "cpu/exec/helper.h"

/* * 这里必须使用 make_helper() 来声明函数原型。
 * 不要使用 make_helper_v()，因为它会生成函数体导致重复定义或语法错误。
 */

// 声明 _v 版本 (用于多字节 opcode)
make_helper(je_si_v);
make_helper(jz_si_v);
make_helper(jne_si_v);
make_helper(jnz_si_v);
make_helper(js_si_v);
make_helper(jns_si_v);
make_helper(jg_si_v);
make_helper(jge_si_v);
make_helper(jl_si_v);
make_helper(jle_si_v);
make_helper(ja_si_v);
make_helper(jae_si_v);
make_helper(jb_si_v);
make_helper(jbe_si_v);
make_helper(jp_si_v);
make_helper(jnp_si_v);
make_helper(jo_si_v);
make_helper(jno_si_v);

// 声明 _b 版本 (用于单字节 opcode 0x70-0x7F)
int je_si_b(swaddr_t eip);
int jz_si_b(swaddr_t eip);
int jne_si_b(swaddr_t eip);
int jnz_si_b(swaddr_t eip);
int js_si_b(swaddr_t eip);
int jns_si_b(swaddr_t eip);
int jg_si_b(swaddr_t eip);
int jge_si_b(swaddr_t eip);
int jl_si_b(swaddr_t eip);
int jle_si_b(swaddr_t eip);
int ja_si_b(swaddr_t eip);
int jae_si_b(swaddr_t eip);
int jb_si_b(swaddr_t eip);
int jbe_si_b(swaddr_t eip);
int jp_si_b(swaddr_t eip);
int jnp_si_b(swaddr_t eip);
int jo_si_b(swaddr_t eip);
int jno_si_b(swaddr_t eip);

#endif
