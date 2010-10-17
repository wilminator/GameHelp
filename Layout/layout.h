#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "dimension.h"

#define LAYOUT_TOP      AXIS_MINIMAL
#define LAYOUT_MIDDLE   AXIS_MEDIAN
#define LAYOUT_BOTTOM   AXIS_MAXIMAL
#define LAYOUT_HEIGHT   AXIS_LENGTH

#define LAYOUT_LEFT     AXIS_MINIMAL
#define LAYOUT_CENTER   AXIS_MEDIAN
#define LAYOUT_RIGHT    AXIS_MAXIMAL
#define LAYOUT_WIDTH    AXIS_LENGTH

typedef struct layout layout;

struct layout{
    dimension external;
    dimension internal;

    // This object is a singly linked list and tree node.
    layout* parent;
    layout* next;
    layout* children;

    // There is some external renderable associated with this layout object.
    void* renderable;
};

#endif // __LAYOUT_H__
