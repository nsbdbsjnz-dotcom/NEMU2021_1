#include "cpu/exec/helper.h"

// 引入不同位宽的模板
// _b = byte (8位), _v = variant (16位或32位)
#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE

// 注册具体的指令入口函数 (make_helper_v 会自动根据操作数大小调用对应的模板)
// 这些需要在 nemu/include/cpu/exec/helper.h 或 all-instr.h 中声明
/* 注意：你需要确保 exec.c 或 decode.c 中的 opcode_table 指向了这些函数
   通常这一步框架已经帮你做了一部分，或者你需要去 nemu/src/cpu/exec/all-instr.h 查看
*/
make_helper_v(add_i2a)
make_helper_v(add_i2rm)
make_helper_v(add_r2rm)
make_helper_v(add_rm2r)