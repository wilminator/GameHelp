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
void get_internal_top(layout* object) {
    return object->internal.top;
}

void get_internal_bottom(layout* object) {
    return object->internal.bottom;
}

void get_internal_width(layout* object) {
    return fabs(object->internal.top - object->internal.bottom);
}

void get_internal_middle(layout* object) {
    return (object->internal.top + object->internal.bottom) / 2.0;
}

void get_internal_left(layout* object) {
    return object->internal.left;
}

void get_internal_right(layout* object) {
    return object->internal.right;
}

void get_internal_width(layout* object) {
    return fabs(object->internal.left - object->internal.right);
}

void get_internal_center(layout* object) {
    return (object->internal.left + object->internal.right) / 2.0;
}

/*
External dimensions- describes this object's position and size
relative to its parent's coordinate system
*/
void get_external_top(layout* object) {
    return object->external.top;
}

void get_external_bottom(layout* object) {
    return object->external.bottom;
}

void get_external_width(layout* object) {
    return fabs(object->external.top - object->external.bottom);
}

void get_external_middle(layout* object) {
    return (object->external.top + object->external.bottom) / 2.0;
}

void get_external_left(layout* object) {
    return object->external.left;
}

void get_external_right(layout* object) {
    return object->external.right;
}

void get_external_width(layout* object) {
    return fabs(object->external.left - object->external.right);
}

void get_external_center(layout* object) {
    return (object->external.left + object->external.right) / 2.0;
}

/*
Priority manipulation
Provides control over how manipulating dimensions is handled.
*/
void set_vertial_priority(layout* object, unsigned int flags) {
    // Limit the flag bits to appropriate vaules.
    flags &= LAYOUT_VERICAL_MASK;
    // Zero affected flag bits in the object.
    object->flags &= ~LAYOUT_VERICAL_MASK;
    // Merge the new flag settings into the object.
    object->flags |= flags;
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
