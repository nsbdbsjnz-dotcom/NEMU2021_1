#include "common.h"
#include "memory/cache.h" // 引入我们写的头文件
#include "device/mmio.h"  // 引入 MMIO 判断

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/* Memory accessing interfaces */

// 物理地址读取
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
    // 如果是设备地址 (MMIO)，直接读设备，不经过 Cache
    int map_idx = is_mmio(addr);
    if (map_idx != -1) {
        return mmio_read(addr, len, map_idx);
    }
    
    // 普通内存地址，走 Cache
    return cache_read(addr, len) & (~0u >> ((4 - len) << 3));
}

// 物理地址写入
void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
    // 如果是设备地址，直接写设备
    int map_idx = is_mmio(addr);
    if (map_idx != -1) {
        mmio_write(addr, len, data, map_idx);
    } else {
        // 普通内存地址，走 Cache
        cache_write(addr, len, data);
    }
}

// 线性地址读取 (PA3后期做页表时修改这里，目前保持原样)
uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
    return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
    hwaddr_write(addr, len, data);
}

// 虚拟地址读取
uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
    assert(len == 1 || len == 2 || len == 4);
#endif
    return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
    assert(len == 1 || len == 2 || len == 4);
#endif
    lnaddr_write(addr, len, data);
}