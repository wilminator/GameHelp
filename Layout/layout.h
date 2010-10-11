#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "dimension.h"

#define LAYOUT_TOP      1
#define LAYOUT_MIDDLE   2
#define LAYOUT_BOTTOM   3
#define LAYOUT_HEIGHT   4

#define LAYOUT_LEFT     5
#define LAYOUT_CENTER   6
#define LAYOUT_RIGHT    7
#define LAYOUT_WIDTH    8

typedef struct layout layout;

struct layout{
    dimension external;
    dimension internal;

    // This object is a singly linked list and tree node.
    layout* parent;
    layout* next;

    // There is some external renderable associated with this layout object.
    void* renderable;
};



#endif // __LAYOUT_H__
