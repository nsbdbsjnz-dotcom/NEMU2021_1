#include "cpu/reg.h"

static const int parity_table [] = {
	0, 1, 0, 1,
	1, 0, 1, 0,
	0, 1, 0, 1,
	1, 0, 1, 0
};

void update_eflags_pf_zf_sf(uint32_t result) {
	uint8_t temp = result & 0xff;
	cpu.eflags.PF = parity_table[temp & 0xf] ^ parity_table[temp >> 4];
	cpu.eflags.ZF = (result == 0);
	cpu.eflags.SF = result >> 31;
}

// 添加完整的标志位更新函数
void update_eflags(uint32_t result, uint32_t src, uint32_t dest, bool is_add) {
    // 更新 PF, ZF, SF
    update_eflags_pf_zf_sf(result);
    
    // 更新 CF
    if (is_add) {
        if (DATA_BYTE == 1) {
            cpu.eflags.CF = (uint8_t)result < (uint8_t)src;
        } else if (DATA_BYTE == 2) {
            cpu.eflags.CF = (uint16_t)result < (uint16_t)src;
        } else {
            cpu.eflags.CF = result < src;
        }
    } else {
        if (DATA_BYTE == 1) {
            cpu.eflags.CF = (uint8_t)dest < (uint8_t)src;
        } else if (DATA_BYTE == 2) {
            cpu.eflags.CF = (uint16_t)dest < (uint16_t)src;
        } else {
            cpu.eflags.CF = dest < src;
        }
    }
    
    // 更新 OF
    if (is_add) {
        cpu.eflags.OF = ((src ^ result) & (dest ^ result)) & MSB(1);
    } else {
        cpu.eflags.OF = ((src ^ dest) & (src ^ result)) & MSB(1);
    }
    
    // 更新 AF
    if (is_add) {
        cpu.eflags.AF = (((src & 0xf) + (dest & 0xf)) & 0x10) != 0;
    } else {
        cpu.eflags.AF = (((dest & 0xf) - (src & 0xf)) & 0x10) != 0;
    }
}