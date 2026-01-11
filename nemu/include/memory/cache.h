#ifndef __CACHE_H__
#define __CACHE_H__

#include "common.h"

// 声明 Cache 对外接口
void init_cache();
uint32_t cache_read(hwaddr_t addr, size_t len);
void cache_write(hwaddr_t addr, size_t len, uint32_t data);

#endif