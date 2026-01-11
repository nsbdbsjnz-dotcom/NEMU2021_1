#ifndef __JCC_H__
#define __JCC_H__

// 声明 _v 版本的 helper (多字节操作码用)
make_helper_v(je_si);
make_helper_v(jz_si);
make_helper_v(jne_si);
make_helper_v(jnz_si);
make_helper_v(js_si);
make_helper_v(jns_si);
make_helper_v(jg_si);
make_helper_v(jge_si);
make_helper_v(jl_si);
make_helper_v(jle_si);
make_helper_v(ja_si);
make_helper_v(jae_si);
make_helper_v(jb_si);
make_helper_v(jbe_si);
make_helper_v(jp_si);
make_helper_v(jnp_si);
make_helper_v(jo_si);
make_helper_v(jno_si);

// 声明 _b 版本的 helper (单字节操作码 0x70-0x7F 用)
// exec.c 直接使用了这些名字
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