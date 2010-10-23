#include "dimension.h"
#include <math.h>

/* Internal functions */

const float axis_get_minimal(const axis* object) {
    return object->minimal;
}

const float axis_get_maximal(const axis* object) {
    return object->maximal;
}

const float axis_get_length(const axis* object) {
    return fabs(object->maximal - object->minimal);
}

const float axis_get_real_length(const axis* object) {
    return object->maximal - object->minimal;
}

const float axis_get_median(const axis* object){
    return (object->minimal + object->maximal) / 2.0;
}

void axis_set_minimal(axis* object, const float value, const unsigned int priority) {
    switch (priority) {
        case AXIS_MEDIAN: // Keep the median of this object constant.
            /*
            int median = (axis_get_maximal(object) + axis_get_minimal(object)) / 2.0;
            object->maximal = median * 2 - value;
            */
            object->maximal += axis_get_minimal(object) - value;
            break;
        case AXIS_MAXIMAL: // Keep the maximal of this object constant.
            //Do nothing.
            break;
        default: // Including AXIS_LENGTH,
                 // keep the length of this object constant
            /*
            float length = axis_get_maximal(object) - axis_get_minimal(object);
            object->maximal = value + length;
            */
            object->maximal += value - axis_get_minimal(object);
    }
    object->minimal = value;
}

void axis_set_maximal(axis* object, const float value, const unsigned int priority) {
    switch (priority) {
        case AXIS_MEDIAN: // Keep the median of this object constant.
            /*
            int median = (object->maximal + object->minimal) / 2.0;
            object->minimal = median * 2 - value;
            */
            object->minimal += axis_get_maximal(object) - value;
            break;
        case AXIS_MINIMAL: // Keep the minimal of this object constant.
            //Do nothing.
            break;
        default: // Including AXIS_LENGTH,
                 // keep the length of this object constant
            /*
            float length = axis_get_maximal(object) - axis_get_minimal(object);
            object->maximal = value - length;
            */
            object->maximal += value - axis_get_maximal(object);
    }
    object->maximal = value;
}

void axis_set_length(axis* object, const float value, const unsigned int priority) {
    // If minimal is less than maximal, then normal is value, else normal is -value.
    float normal = (axis_get_minimal(object) < axis_get_maximal(object)) ? value : -value;
    switch (priority) {
        case AXIS_MINIMAL: // Keep the minimal of this object constant.
            object->maximal = axis_get_minimal(object) + normal;
            break;
        case AXIS_MAXIMAL: // Keep the maximal of this object constant.
            object->minimal = axis_get_maximal(object) - normal;
            break;
        default: // Including AXIS_MEDIAN,
                 // keep the median of this object constant
            {
                float median = axis_get_median(object);
                object->minimal = median - normal / 2.0;
                object->maximal = median + normal / 2.0;
            }
    }
}

void axis_set_median(axis* object, const float value, const unsigned int priority) {
    switch (priority) {
        case AXIS_MINIMAL: // Keep the minimal of this object constant.
            object->maximal = value * 2.0 - axis_get_minimal(object);
            break;
        case AXIS_MAXIMAL: // Keep the maximal of this object constant.
            object->minimal = value * 2.0 - axis_get_maximal(object);
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

axis axis_convert_coordinate_system(axis* initial, axis* internal, axis* external) {
    axis result;
    float internal_length = axis_get_real_length(internal);
    float internal_minimal = axis_get_minimal(internal);
    float external_length = axis_get_real_length(external);
    float external_minimal = axis_get_minimal(external);
    float minimal_ratio;
    float maximal_ratio;

    // If there is no internal length, then just return the external axis.
    if (internal_length == 0.0) {
        return *external;
    }

    //Get the ratio of the initial bounds and the length of the internal coordinate system.
    minimal_ratio = axis_get_minimal(initial) - internal_minimal / internal_length;
    maximal_ratio = axis_get_maximal(initial) - internal_minimal / internal_length;

    //Calculate these in terms of the external coordinate system.
    axis_set_minimal(&result, external_minimal + external_length * minimal_ratio, AXIS_MINIMAL);
    axis_set_maximal(&result, external_minimal + external_length * maximal_ratio, AXIS_MAXIMAL);

    return result;
}

/* Externally available functions */

const float dimension_get_top(const dimension* object) {
    return axis_get_minimal(&object->vertical);
}

const float dimension_get_bottom(const dimension* object) {
    return axis_get_maximal(&object->vertical);
}

const float dimension_get_height(const dimension* object) {
    return axis_get_length(&object->vertical);
}

const float dimension_get_middle(const dimension* object) {
    return axis_get_median(&object->vertical);
}

const float dimension_get_left(const dimension* object) {
    return axis_get_minimal(&object->horizontal);
}

const float dimension_get_right(const dimension* object) {
    return axis_get_maximal(&object->horizontal);
}

const float dimension_get_width(const dimension* object) {
    return axis_get_length(&object->horizontal);
}

const float dimension_get_center(const dimension* object) {
    return axis_get_median(&object->horizontal);
}

void dimension_set_top(dimension* object, const float value, const unsigned int priority) {
    axis_set_minimal(&object->vertical, value, priority);
}

void dimension_set_bottom(dimension* object, const float value, const unsigned int priority) {
    axis_set_maximal(&object->vertical, value, priority);
}

void dimension_set_height(dimension* object, const float value, const unsigned int priority) {
    axis_set_length(&object->vertical, value, priority);
}

void dimension_set_middle(dimension* object, const float value, const unsigned int priority) {
    axis_set_median(&object->vertical, value, priority);
}

void dimension_set_left(dimension* object, const float value, const unsigned int priority) {
    axis_set_minimal(&object->horizontal, value, priority);
}

void dimension_set_right(dimension* object, const float value, const unsigned int priority) {
    axis_set_maximal(&object->horizontal, value, priority);
}

void dimension_set_width(dimension* object, const float value, const unsigned int priority) {
    axis_set_length(&object->horizontal, value, priority);
}

void dimension_set_center(dimension* object, const float value, const unsigned int priority) {
    axis_set_median(&object->horizontal, value, priority);
}

/* Size resolution functions */
dimension dimension_convert_coordinate_system(dimension* child_external, dimension* parent_internal, dimension* parent_actual) {
    /* Calculate the size ratio of initial vs. internal,
       then express that ratio in terms of external. */
    dimension result;
    result.horizontal = axis_convert_coordinate_system(&child_external->horizontal , &parent_internal->horizontal, &parent_actual->horizontal);
    result.vertical = axis_convert_coordinate_system(&child_external->vertical , &parent_internal->vertical, &parent_actual->vertical);
    return result;
}
