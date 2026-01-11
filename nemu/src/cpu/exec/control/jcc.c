#include "cpu/exec/helper.h"

// 定义 DATA_BYTE 为 1、2 和 4，分别生成 8 位、16 位和 32 位的条件跳转指令

// 8位条件跳转指令
#define DATA_BYTE 1
#include "jcc-template.h"

// 16位条件跳转指令
#define DATA_BYTE 2
#include "jcc-template.h"

// 32位条件跳转指令
#define DATA_BYTE 4
#include "jcc-template.h"

#undef DATA_BYTE

// 使用make_helper_v宏为所有条件跳转指令创建通用版本
make_helper_v(jz_si)
make_helper_v(jnz_si)
make_helper_v(jg_si)
make_helper_v(jl_si)
make_helper_v(jge_si)
make_helper_v(jle_si)
make_helper_v(ja_si)
make_helper_v(jb_si)
make_helper_v(jae_si)
make_helper_v(jbe_si)