#include "RotateCache.h"
#include <stdlib.h>

sequential_cache* create_sequential_cache(const unsigned int count) {
    sequential_cache* cache = (sequential_cache*) calloc(1, sizeof(sequential_cache));
    cache->items = (void**) calloc(count, sizeof(void*));
    cache->count = count;
    return cache;
}

void* get_item_from_cache(const sequential_cache* cache, const unsigned int index) {
    int fixed_index = index % cache->count;
    return cache->items[fixed_index];
}

void put_item_in_cache(sequential_cache* cache, const unsigned int index, void* item) {
    int fixed_index = index % cache->count;
    cache->items[fixed_index] = item;
}

void delete_sequential_cache(sequential_cache* cache) {
    free(cache);
}

sequential_cache* create_populated_sequential_cache(const unsigned int count, void* (*callback)(const unsigned int, void*), void* params) {
    sequential_cache* cache = create_sequential_cache(count);
    int index;
    void* item;
    for (index = 0; index < count; index++) {
        item = (*callback)(index, params);
        put_item_in_cache(cache, index, item);
    }
    return cache;
}
