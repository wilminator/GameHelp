#include "dimension.h"

float get_top(dimension object) {
    return object.top;
}

float get_bottom(dimension object) {
    return object.bottom;
}

float get_height(dimension object) {
    return fabs(object.top - object.bottom);
}

float get_middle(dimension object) {
    return (object.top + object.bottom) / 2.0;
}

float get_left(dimension object) {
    return object.left;
}

float get_right(dimension object) {
    return object.right;
}

float get_width(dimension object) {
    return fabs(object.left - object.right);
}

float get_center(dimension object) {
    return (object.left + object.right) / 2.0;
}

