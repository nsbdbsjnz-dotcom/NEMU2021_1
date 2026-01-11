#include "common.h"
#include "memory/cache.h"
#include <time.h>
#include <stdlib.h>

// 声明 memory.c 或 dram.c 中的读写函数
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

// Cache 配置参数 (符合PA3一般要求)
#define CACHE_SIZE (64 * 1024)  // 64KB 总大小
#define BLOCK_SIZE 64           // 64 Bytes 块大小
#define WAY_NUM 8               // 8路组相联
#define GROUP_NUM (CACHE_SIZE / (BLOCK_SIZE * WAY_NUM)) // 组数 = 128

// Cache 行结构定义
typedef struct {
    bool valid;      // 有效位
    uint32_t tag;    // 标记位
    uint8_t data[BLOCK_SIZE]; // 数据块
} CacheLine;

CacheLine cache[GROUP_NUM][WAY_NUM];

// 初始化函数
void init_cache() {
    for (int i = 0; i < GROUP_NUM; i++) {
        for (int j = 0; j < WAY_NUM; j++) {
            cache[i][j].valid = false;
        }
    }
}

// 辅助函数：解析地址
// 地址格式: [ Tag (19bit) | Group Index (7bit) | Block Offset (6bit) ]
static uint32_t parse_tag(hwaddr_t addr) { return addr >> 13; }
static uint32_t parse_group(hwaddr_t addr) { return (addr >> 6) & (GROUP_NUM - 1); }
static uint32_t parse_offset(hwaddr_t addr) { return addr & (BLOCK_SIZE - 1); }

// Cache 读取函数
uint32_t cache_read(hwaddr_t addr, size_t len) {
    uint32_t tag = parse_tag(addr);
    uint32_t group = parse_group(addr);
    uint32_t offset = parse_offset(addr);

    // 1. 查找是否命中 (Hit)
    for (int i = 0; i < WAY_NUM; i++) {
        if (cache[group][i].valid && cache[group][i].tag == tag) {
            // 命中！处理数据读取
            // 注意：如果数据跨越了两个Block (例如读在 62 字节处，读 4 字节)
            if (offset + len > BLOCK_SIZE) {
                // 简单处理：跨行情况直接回退到读内存 (或分别读两次Cache)
                // 这里为了稳健，简单调用 dram_read
                return dram_read(addr, len); 
            }
            
            // 正常命中读取
            uint32_t ret = 0;
            memcpy(&ret, &cache[group][i].data[offset], len);
            return ret;
        }
    }

    // 2. 未命中 (Miss) -> 读取内存并填入 Cache
    // 随机替换策略 (Random Replacement)
    int way = 0;
    // 先找空闲行
    for (int i = 0; i < WAY_NUM; i++) {
        if (!cache[group][i].valid) { way = i; break; }
        if (i == WAY_NUM - 1) way = rand() % WAY_NUM; // 没空位，随机选一个
    }

    // 将内存块加载到 Cache 行
    // 注意要对齐到块边界
    hwaddr_t block_start = addr & ~(BLOCK_SIZE - 1);
    for (int k = 0; k < BLOCK_SIZE; k++) {
        cache[group][way].data[k] = (uint8_t)dram_read(block_start + k, 1);
    }
    cache[group][way].tag = tag;
    cache[group][way].valid = true;

    // 返回刚才请求的数据
    uint32_t ret = 0;
    memcpy(&ret, &cache[group][way].data[offset], len);
    return ret;
}

// Cache 写入函数 (Write Through + No Write Allocate)
void cache_write(hwaddr_t addr, size_t len, uint32_t data) {
    uint32_t tag = parse_tag(addr);
    uint32_t group = parse_group(addr);
    uint32_t offset = parse_offset(addr);

    // 1. 总是直接写回内存 (Write Through)
    dram_write(addr, len, data);

    // 2. 如果 Cache 中有这份数据，也要更新 Cache (保持一致性)
    for (int i = 0; i < WAY_NUM; i++) {
        if (cache[group][i].valid && cache[group][i].tag == tag) {
            // 命中：更新 Cache
            if (offset + len > BLOCK_SIZE) return; // 跨行忽略
            memcpy(&cache[group][i].data[offset], &data, len);
            return;
        }
    }
    // 未命中：什么都不做 (No Write Allocate)
}