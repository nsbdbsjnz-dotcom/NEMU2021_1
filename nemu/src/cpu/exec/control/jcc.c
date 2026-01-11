#include "cpu/exec/helper.h"

// 1. 生成 8位 (short jump) 的逻辑 -> 函数名为 jcc_si_b
#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

// 2. 生成 16位 (near jump) 的逻辑 -> 函数名为 jcc_si_w
#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

// 3. 生成 32位 (near jump) 的逻辑 -> 函数名为 jcc_si_l
#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE

/* 注册函数接口 */

// 定义宏来简化重复代码
// SUFFIX 为 _b (对于 0x7x 系列指令)
// 或者 _v (对于 0x0F 0x8x 系列指令)
#define H(name) make_helper_v(name ## _si)
#define H_b(name) make_helper(name ## _si_b)

/* --- 0x7x: Short Jumps (8-bit offset) --- */
H_b(jo);  H_b(jno);
H_b(jb);  H_b(jae);
H_b(je);  H_b(jne);
H_b(jbe); H_b(ja);
H_b(js);  H_b(jns);
H_b(jp);  H_b(jnp);
H_b(jl);  H_b(jge);
H_b(jle); H_b(jg);

/* --- 0x0F 8x: Near Jumps (16/32-bit offset) --- */
H(jo);  H(jno);
H(jb);  H(jae);
H(je);  H(jne);
H(jbe); H(ja);
H(js);  H(jns);
H(jp);  H(jnp);
H(jl);  H(jge);
H(jle); H(jg);

// 别名处理 (JZ=JE, JNZ=JNE 等)
make_helper(jz_si_b);  // 0x74
make_helper(jnz_si_b); // 0x75
make_helper_v(jz_si);  // 0x0F 0x84
make_helper_v(jnz_si); // 0x0F 0x85
#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE

/* 注册所有 Jcc 指令 */
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
// 新增部分
make_helper_v(jp_si)
make_helper_v(jnp_si)
make_helper_v(jo_si)
make_helper_v(jno_si)