#include "cpu/exec/helper.h"

// 1. 生成 8位 形式 (例如 jz_si_b)
#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

// 2. 生成 16位 形式 (例如 jz_si_w)
#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

// 3. 生成 32位 形式 (例如 jz_si_l)
#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE

/* 注册函数接口 */
// 注意：这里只注册通用接口 _v，单字节接口 _b 是硬编码在 exec.c 里的，不需要 make_helper_v
make_helper_v(je_si)
make_helper_v(jz_si)
make_helper_v(jne_si)
make_helper_v(jnz_si)
make_helper_v(js_si)
make_helper_v(jns_si)
make_helper_v(jg_si)
make_helper_v(jge_si)
make_helper_v(jl_si)
make_helper_v(jle_si)
make_helper_v(ja_si)
make_helper_v(jae_si)
make_helper_v(jb_si)
make_helper_v(jbe_si)
make_helper_v(jp_si)
make_helper_v(jnp_si)
make_helper_v(jo_si)
make_helper_v(jno_si)