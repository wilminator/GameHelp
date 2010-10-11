#include "dimension.h"
#include <math.h>

float get_minimal(axis* object) {
    return object->minimal;
}

float get_maximal(axis* object) {
    return object->maximal;
}

float get_length(axis* object) {
    return fabs(object->maximal - object->minimal);
}

float get_median(axis* object){
    return (object->minimal + object->maximal) / 2.0;
}

float get_top(dimension* object) {
    return get_minimal(&object->vertical);
}

float get_bottom(dimension* object) {
    return get_maximal(&object->vertical);
}

float get_height(dimension* object) {
    return get_length(&object->vertical);
}

float get_middle(dimension* object) {
    return get_median(&object->vertical);
}

float get_left(dimension* object) {
    return get_minimal(&object->horizontal);
}

float get_right(dimension* object) {
    return get_maximal(&object->horizontal);
}

float get_width(dimension* object) {
    return get_length(&object->horizontal);
}

float get_center(dimension* object) {
    return get_median(&object->horizontal);
}

void set_minimal(axis* object, float value, unsigned int priority) {
    switch (priority) {
        case AXIS_MEDIAN: // Keep the median of this object constant.
            /*
            int median = (get_maximal(object) + get_minimal(object)) / 2.0;
            object->maximal = median * 2 - value;
            */
            object->maximal += get_minimal(object) - value;
            break;
        case AXIS_MAXIMAL: // Keep the maximal of this object constant.
            //Do nothing.
            break;
        default: // Including AXIS_LENGTH,
                 // keep the length of this object constant
            /*
            float length = get_maximal(object) - get_minimal(object);
            object->maximal = value + length;
            */
            object->maximal += value - get_minimal(object);
    }
    object->minimal = value;
}

void set_maximal(axis* object, float value, unsigned int priority) {
    switch (priority) {
        case AXIS_MEDIAN: // Keep the median of this object constant.
            /*
            int median = (object->maximal + object->minimal) / 2.0;
            object->minimal = median * 2 - value;
            */
            object->minimal += get_maximal(object) - value;
            break;
        case AXIS_MINIMAL: // Keep the minimal of this object constant.
            //Do nothing.
            break;
        default: // Including AXIS_LENGTH,
                 // keep the length of this object constant
            /*
            float length = get_maximal(object) - get_minimal(object);
            object->maximal = value - length;
            */
            object->maximal += value - get_maximal(object);
    }
    object->maximal = value;
}

void set_length(axis* object, float value, unsigned int priority) {
    // If minimal is less than maximal, then normal is value, else normal is -value.
    float normal = (get_minimal(object) < get_maximal(object)) ? value : -value;
    switch (priority) {
        case AXIS_MINIMAL: // Keep the minimal of this object constant.
            object->maximal = get_minimal(object) + normal;
            break;
        case AXIS_MAXIMAL: // Keep the maximal of this object constant.
            object->minimal = get_maximal(object) - normal;
            break;
        default: // Including AXIS_MEDIAN,
                 // keep the median of this object constant
            {
                float median = get_median(object);
                object->minimal = median - normal / 2.0;
                object->maximal = median + normal / 2.0;
            }
    }
}

void set_median(axis* object, float value, unsigned int priority) {
    switch (priority) {
        case AXIS_MINIMAL: // Keep the minimal of this object constant.
            object->maximal = value * 2.0 - get_minimal(object);
            break;
        case AXIS_MAXIMAL: // Keep the maximal of this object constant.
            object->minimal = value * 2.0 - get_maximal(object);
            break;
        default: // Including AXIS_LENGTH,
                 // keep the length of this object constant
            {
                int length = object->maximal - object->minimal;
                object->minimal = value - length / 2.0;
                object->maximal = value + length / 2.0;
            }
    }
}

void set_top(dimension* object, float value, unsigned int priority) {
    set_minimal(&object->vertical, value, priority);
}

void set_bottom(dimension* object, float value, unsigned int priority) {
    set_maximal(&object->vertical, value, priority);
}

void set_height(dimension* object, float value, unsigned int priority) {
    set_length(&object->vertical, value, priority);
}

void set_middle(dimension* object, float value, unsigned int priority) {
    set_median(&object->vertical, value, priority);
}

void set_left(dimension* object, float value, unsigned int priority) {
    set_minimal(&object->horizontal, value, priority);
}

void set_right(dimension* object, float value, unsigned int priority) {
    set_maximal(&object->horizontal, value, priority);
}

void set_width(dimension* object, float value, unsigned int priority) {
    set_length(&object->horizontal, value, priority);
}

void set_center(dimension* object, float value, unsigned int priority) {
    set_median(&object->horizontal, value, priority);
}

