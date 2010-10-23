#ifndef __ROTATECACHE_H__
#define __ROTATECACHE_H__

struct sequential_cache {
    unsigned int count;
    void** items;
};

typedef struct sequential_cache sequential_cache;

struct animation_frame {
    void* image;
    unsigned int delay;
};

typedef struct animation_frame animation_frame;

sequential_cache* create_sequential_cache(const unsigned int count);
void* get_item_from_cache(const sequential_cache* cache, const unsigned int index);
void put_item_in_cache(sequential_cache* cache, const unsigned int index, void* item);
void delete_sequential_cache(sequential_cache* cache);

sequential_cache* create_populated_sequential_cache(const unsigned int count, void* (*callback)(const unsigned int, void*), void* params);

#endif //__ROTATECACHE_H__
