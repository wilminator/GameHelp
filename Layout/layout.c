#include "layout.h"
#include <mem.h>


/*
Base emmory management functions.
*/
layout* create_layout(void) {
    layout *object = (layout*) calloc(1, sizeof(layout));
    return object;
}

void delete_layout(layout* object) {
    free(object);
}

/*
Internal dimensions- describes this object's internal coordinate system.
Child objects are positioned relatively based on these parameters.
*/
float get_internal_top(layout* object) {
    return get_top(object->internal);
}

float get_internal_bottom(layout* object) {
    return get_bottom(object->internal);
}

float get_internal_height(layout* object) {
    return get_height(object->internal);
}

float get_internal_middle(layout* object) {
    return get_middle(object->internal);
}

float get_internal_left(layout* object) {
    return get_left(object->internal);
}

float get_internal_right(layout* object) {
    return get_right(object->internal);
}

float get_internal_width(layout* object) {
    return get_width(object->internal);
}

float get_internal_center(layout* object) {
    return get_center(object->internal);
}

/*
External dimensions- describes this object's position and size
relative to its parent's coordinate system
*/
float get_external_top(layout* object) {
    return get_top(object->external);
}

float get_external_bottom(layout* object) {
    return get_bottom(object->external);
}

float get_external_height(layout* object) {
    return get_height(object->external);
}

float get_external_middle(layout* object) {
    return get_middle(object->external);
}

float get_external_left(layout* object) {
    return get_left(object->external);
}

float get_external_right(layout* object) {
    return get_right(object->external);
}

float get_external_width(layout* object) {
    return get_width(object->external);
}

float get_external_center(layout* object) {
    return get_center(object->external);
}

/*
Internal dimension manipulation
These functions change the internal dimension values for this object.
The appropriate priorty flags are used to determine which values are
actually modified when setting a value.

Note that the coordinate system is completely arbitrary.  This means that
you can have increasing y values mean further down from the top of the screen
(traditional 2D rendering coordinate system) or increasing y values mean
further up on the screen (traditional mathematical cartesian coordinates).  As
fair warning, this means that the top value can acceptably be greater or less
than the bottom value.
*/
void set_internal_top(layout* object, float value, unsigned int priority = LAYOUT_HEIGHT) {
    switch (priority) {
        case LAYOUT_MIDDLE: // Keep the middle of this object constant.
            int middle = (object->internal.top + object->internal.bottom) / 2.0;
            object->internal.bottom = middle * 2 - value
            break;
        case LAYOUT_BOTTOM: // Keep the bottom of this object constant.
            //Do nothing.
            break;
        default: // Including LAYOUT_HEIGHT,
                 // keep the height of this object constant
            float height = object->bottom - object->internal.top;
            object->internal.bottom = value + height;
    }
    object->internal.top = value;
}

void set_internal_bottom(layout* object, float value, unsigned int priority = LAYOUT_HEIGHT) {
    switch (priority) {
        case LAYOUT_MIDDLE: // Keep the middle of this object constant.
            int middle = (object->internal.bottom + object->internal.top) / 2.0;
            object->internal.top = middle * 2 - value
            break;
        case LAYOUT_TOP: // Keep the top of this object constant.
            //Do nothing.
            break;
        default: // Including LAYOUT_HEIGHT,
                 // keep the height of this object constant
            float height = object->internal.bottom - object->internal.top;
            object->internal.bottom = value - height;
    }
    object->internal.bottom = value;
}

void set_internal_height(layout* object, float value, unsigned int priority = LAYOUT_MIDDLE) {
    // If top is less than bottom, then normal is value, else normal is -value.
    float normal = (get_internal_top(object) < get_internal_bottom(object)) ? value : -value;
    switch (priority) {
        case LAYOUT_TOP: // Keep the top of this object constant.
            object->internal.bottom = object->internal.top + value
            break;
        case LAYOUT_BOTTOM: // Keep the bottom of this object constant.
            object->internal.top = object->internal.bottom - value
            break;
        default: // Including LAYOUT_MIDDLE,
                 // keep the middle of this object constant
            int middle = get_internal_middle(object);
            object->internal.top = middle - value / 2.0;
            object->internal.bottom = middle + value / 2.0;
    }
}

void set_internal_middle(layout* object, float value, unsigned int priority = LAYOUT_HEIGHT) {
    switch (priority) {
        case LAYOUT_TOP: // Keep the top of this object constant.
            object->internal.bottom = value * 2.0 - object->internal.top;
            break;
        case LAYOUT_BOTTOM: // Keep the bottom of this object constant.
            object->internal.top = value * 2.0 - object->internal.bottom;
            break;
        default: // Including LAYOUT_HEIGHT,
                 // keep the height of this object constant
            int height = object->internal.bottom - object->internal.top;
            object->internal.top = value - height / 2.0;
            object->internal.bottom = value + height / 2.0;
    }
}

void set_internal_left(layout* object, float value, unsigned int priority = LAYOUT_WIDTH) {
    switch (priority) {
        case LAYOUT_CENTER: // Keep the center of this object constant.
            int center = (object->internal.left + object->internal.right) / 2.0;
            object->internal.right = center * 2 - value
            break;
        case LAYOUT_RIGHT: // Keep the right of this object constant.
            //Do nothing.
            break;
        default: // Including LAYOUT_WIDTH,
                 // keep the width of this object constant
            float width = object->right - object->internal.left;
            object->internal.right = value + width;
    }
    object->internal.left = value;
}

void set_internal_right(layout* object, float value, unsigned int priority = LAYOUT_WIDTH) {
    switch (priority) {
        case LAYOUT_CENTER: // Keep the middle of this object constant.
            int center = (object->internal.right + object->internal.left) / 2.0;
            object->internal.left = center * 2 - value
            break;
        case LAYOUT_LEFT: // Keep the left of this object constant.
            //Do nothing.
            break;
        default: // Including LAYOUT_WIDTH,
                 // keep the width of this object constant
            float width = object->internal.right - object->internal.left;
            object->internal.right = value - width;
    }
    object->internal.right = value;
}

void set_internal_width(layout* object, float value, unsigned int priority = LAYOUT_CENTER) {
    // If left is less than right, then normal is value, else normal is -value.
    float normal = (get_internal_left(object) < get_internal_right(object)) ? value : -value;
    switch (priority) {
        case LAYOUT_LEFT: // Keep the left of this object constant.
            object->internal.right = object->internal.left + value
            break;
        case LAYOUT_RIGHT: // Keep the right of this object constant.
            object->internal.left = object->internal.right - value
            break;
        default: // Including LAYOUT_CENTER,
                 // keep the center of this object constant
            int center = get_internal_center(object);
            object->internal.left = center - value / 2.0;
            object->internal.right = center + value / 2.0;
    }
}

void set_internal_center(layout* object, float value, unsigned int priority = LAYOUT_WIDTH) {
    switch (priority) {
        case LAYOUT_LEFT: // Keep the left of this object constant.
            object->internal.right = value * 2.0 - object->internal.left;
            break;
        case LAYOUT_RIGHT: // Keep the right of this object constant.
            object->internal.left = value * 2.0 - object->internal.right;
            break;
        default: // Including LAYOUT_WIDTH,
                 // keep the width of this object constant
            int width = object->internal.right - object->internal.left;
            object->internal.left = value - width / 2.0;
            object->internal.right = value + width / 2.0;
    }
}

/*
Child Manipulation
Provides functions used to interface children objects with their parents.
*/
void attach_child(layout* parent,layout* child) {
    child->parent = parent;
    child->next = parent->children;
    parent->children = child;
}

void detach_child(layout* parent, layout* child) {
    layout* index = parent->children;
    if (index == child) {
        parent->children = child->next;
        child
    } else {
        while (index->next != child) {
            // The end of the linked list is null.
            // Exit the function if the index becomed null.
            if (!index) return;
            // Advance to the next item in the list.
            index = index-> next;
        }
        index->next = child->next;
    }
    // Zero the (former) child's linking variables.
    child->parent = NULL;
    child->next = NULL;
}
