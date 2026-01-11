#include "cpu/reg.h"
#include "common.h"

// 初始化 EFLAGS 寄存器
void init_eflags() {
    // EFLAGS 的第1位总是1 (0x2)
    cpu.eflags.val = 0x00000002; 
}

// 实现update_eflags_pf_zf_sf函数
void update_eflags_pf_zf_sf(uint32_t result) {
    // PF (Parity Flag): 奇偶标志 (低8位中1的个数为偶数)
    int val = result & 0xff;
    val ^= val >> 4;
    val ^= val >> 2;
    val ^= val >> 1;
    cpu.eflags.PF = (~val) & 1;

    // ZF (Zero Flag): 零标志
    cpu.eflags.ZF = (result == 0);

    // SF (Sign Flag): 符号标志 - 直接计算最高位
    cpu.eflags.SF = (result >> 31) & 1;
}

/* * 注意：不要在这里写通用的 update_eflags 函数。
 * 因为这里无法使用 DATA_BYTE 宏。
 * 请直接在各指令的 template 文件中计算标志位。
 */