#ifndef __DIMENSION_H__
#define __DIMENSION_H__

struct dimension {
    float top;
    float bottom;
    float left;
    float right;
};

typedef struct dimension dimension;

float get_top(dimension object);
float get_bottom(dimension object);
float get_height(dimension object);
float get_middle(dimension object);
float get_left(dimension object);
float get_right(dimension object);
float get_width(dimension object);
float get_center(dimension object);

#endif // __DIMENSION_H__
