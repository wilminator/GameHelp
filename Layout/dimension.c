#include "dimension.h"
#include <math.h>

const float get_minimal(const axis* object) {
    return object->minimal;
}

const float get_maximal(const axis* object) {
    return object->maximal;
}

const float get_length(const axis* object) {
    return fabs(object->maximal - object->minimal);
}

const float get_median(const axis* object){
    return (object->minimal + object->maximal) / 2.0;
}

const float get_top(const dimension* object) {
    return get_minimal(&object->vertical);
}

const float get_bottom(const dimension* object) {
    return get_maximal(&object->vertical);
}

const float get_height(const dimension* object) {
    return get_length(&object->vertical);
}

const float get_middle(const dimension* object) {
    return get_median(&object->vertical);
}

const float get_left(const dimension* object) {
    return get_minimal(&object->horizontal);
}

const float get_right(const dimension* object) {
    return get_maximal(&object->horizontal);
}

const float get_width(const dimension* object) {
    return get_length(&object->horizontal);
}

const float get_center(const dimension* object) {
    return get_median(&object->horizontal);
}

void set_minimal(axis* object, const float value, const unsigned int priority) {
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

void set_maximal(axis* object, const float value, const unsigned int priority) {
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

void set_length(axis* object, const float value, const unsigned int priority) {
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

void set_median(axis* object, const float value, const unsigned int priority) {
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

void set_top(dimension* object, const float value, const unsigned int priority) {
    set_minimal(&object->vertical, value, priority);
}

void set_bottom(dimension* object, const float value, const unsigned int priority) {
    set_maximal(&object->vertical, value, priority);
}

void set_height(dimension* object, const float value, const unsigned int priority) {
    set_length(&object->vertical, value, priority);
}

void set_middle(dimension* object, const float value, const unsigned int priority) {
    set_median(&object->vertical, value, priority);
}

void set_left(dimension* object, const float value, const unsigned int priority) {
    set_minimal(&object->horizontal, value, priority);
}

void set_right(dimension* object, const float value, const unsigned int priority) {
    set_maximal(&object->horizontal, value, priority);
}

void set_width(dimension* object, const float value, const unsigned int priority) {
    set_length(&object->horizontal, value, priority);
}

void set_center(dimension* object, const float value, const unsigned int priority) {
    set_median(&object->horizontal, value, priority);
}

