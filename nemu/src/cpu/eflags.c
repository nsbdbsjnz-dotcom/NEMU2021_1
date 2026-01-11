#include "cpu/reg.h"
#include "common.h"

// 初始化 EFLAGS 寄存器
void init_eflags() {
    // EFLAGS 的第1位总是1 (0x2)
    cpu.eflags.val = 0x00000002; 
}

/* * 注意：不要在这里写通用的 update_eflags 函数。
 * 因为这里无法使用 DATA_BYTE 宏。
 * 请直接在各指令的 template 文件中计算标志位。
 */