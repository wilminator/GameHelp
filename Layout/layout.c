#include "layout.h"
#include <mem.h>
#include <stdlib.h>

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
    return get_top(&object->internal);
}

float get_internal_bottom(layout* object) {
    return get_bottom(&object->internal);
}

float get_internal_height(layout* object) {
    return get_height(&object->internal);
}

float get_internal_middle(layout* object) {
    return get_middle(&object->internal);
}

float get_internal_left(layout* object) {
    return get_left(&object->internal);
}

float get_internal_right(layout* object) {
    return get_right(&object->internal);
}

float get_internal_width(layout* object) {
    return get_width(&object->internal);
}

float get_internal_center(layout* object) {
    return get_center(&object->internal);
}

/*
External dimensions- describes this object's position and size
relative to its parent's coordinate system
*/
float get_external_top(layout* object) {
    return get_top(&object->external);
}

float get_external_bottom(layout* object) {
    return get_bottom(&object->external);
}

float get_external_height(layout* object) {
    return get_height(&object->external);
}

float get_external_middle(layout* object) {
    return get_middle(&object->external);
}

float get_external_left(layout* object) {
    return get_left(&object->external);
}

float get_external_right(layout* object) {
    return get_right(&object->external);
}

float get_external_width(layout* object) {
    return get_width(&object->external);
}

float get_external_center(layout* object) {
    return get_center(&object->external);
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
void set_internal_top(layout* object, float value, unsigned int priority) {
    set_top(&object->internal, value, priority);
}

void set_internal_bottom(layout* object, float value, unsigned int priority) {
    set_bottom(&object->internal, value, priority);
}

void set_internal_height(layout* object, float value, unsigned int priority) {
    set_height(&object->internal, value, priority);
}

void set_internal_middle(layout* object, float value, unsigned int priority) {
    set_middle(&object->internal, value, priority);
}

void set_internal_left(layout* object, float value, unsigned int priority) {
    set_left(&object->internal, value, priority);
}

void set_internal_right(layout* object, float value, unsigned int priority) {
    set_right(&object->internal, value, priority);
}

void set_internal_width(layout* object, float value, unsigned int priority) {
    set_width(&object->internal, value, priority);
}

void set_internal_center(layout* object, float value, unsigned int priority) {
    set_center(&object->internal, value, priority);
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
