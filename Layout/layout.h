#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#define LAYOUT_TOP      (1<<0)
#define LAYOUT_MIDDLE   (1<<1)
#define LAYOUT_BOTTOM   (1<<2)
#define LAYOUT_HEIGHT   (1<<3)
#define LAYOUT_LEFT     (1<<4)
#define LAYOUT_CENTER   (1<<5)
#define LAYOUT_RIGHT    (1<<6)
#define LAYOUT_WIDTH    (1<<7)

struct dimension {
    float top;
    float bottom;
    float left;
    float right;
};

typedef struct dimension dimension;

typedef struct layout layout;

struct layout{
    dimension external;
    dimension internal;
    unsigned int flags;
    /*
    This object is a singly linked list and tree node.
    */
    layout* parent;
    layout* next;
};



#endif //__LAYOUT_H__
