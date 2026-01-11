#include "common.h"
#include "memory/cache.h"
#include "device/mmio.h"

/* 声明 DRAM 读写函数 (在 dram.c 中) */
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/* 1. 物理地址读取 */
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
    // 检查是否是外设 (MMIO)
    int map_no = is_mmio(addr);
    if (map_no != -1) {
        return mmio_read(addr, len, map_no);
    }
    // 访问 Cache (如果你之前的 cache.c 没写好，这里可以临时改成 return dram_read(addr, len) & ...)
    return cache_read(addr, len) & (~0u >> ((4 - len) << 3));
}

/* 2. 物理地址写入 */
void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
    int map_no = is_mmio(addr);
    if (map_no != -1) {
        mmio_write(addr, len, data, map_no);
    } else {
        cache_write(addr, len, data);
    }
}

/* 3. 线性地址读取 (强行短路) */
uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
    // ❌ 不要检查 CR0 分页位
    // ❌ 不要查页表
    // ✅ 直接当物理地址读
    return hwaddr_read(addr, len);
}

/* 4. 线性地址写入 (强行短路) */
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
    hwaddr_write(addr, len, data);
}

/* 5. 虚拟地址读取 (强行短路) */
uint32_t swaddr_read(swaddr_t addr, size_t len) {
    // ❌ 不要检查段寄存器
    // ✅ 直接当线性地址读
    return lnaddr_read(addr, len);
}

/* 6. 虚拟地址写入 (强行短路) */
void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
    lnaddr_write(addr, len, data);
}