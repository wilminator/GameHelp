#include "layout.h"
#include <mem.h>
#include <stdlib.h>

/*
Base memory management functions.
*/
layout* layout_create(void) {
    layout *object = (layout*) calloc(1, sizeof(layout));
    return object;
}

void layout_delete(layout* object) {
    free(object);
}

/*
Internal dimensions- describes this object's internal coordinate system.
Child objects are positioned relatively based on these parameters.
*/
float layout_get_internal_top(const layout* object) {
    return dimension_get_top(&object->internal);
}

float layout_get_internal_bottom(const layout* object) {
    return dimension_get_bottom(&object->internal);
}

float layout_get_internal_height(const layout* object) {
    return dimension_get_height(&object->internal);
}

float layout_get_internal_middle(const layout* object) {
    return dimension_get_middle(&object->internal);
}

float layout_get_internal_left(const layout* object) {
    return dimension_get_left(&object->internal);
}

float layout_get_internal_right(const layout* object) {
    return dimension_get_right(&object->internal);
}

float layout_get_internal_width(const layout* object) {
    return dimension_get_width(&object->internal);
}

float layout_get_internal_center(const layout* object) {
    return dimension_get_center(&object->internal);
}

/*
External dimensions- describes this object's position and size
relative to its parent's coordinate system
*/
float layout_get_external_top(const layout* object) {
    return dimension_get_top(&object->external);
}

float layout_get_external_bottom(const layout* object) {
    return dimension_get_bottom(&object->external);
}

float layout_get_external_height(const layout* object) {
    return dimension_get_height(&object->external);
}

float layout_get_external_middle(const layout* object) {
    return dimension_get_middle(&object->external);
}

float layout_get_external_left(const layout* object) {
    return dimension_get_left(&object->external);
}

float layout_get_external_right(const layout* object) {
    return dimension_get_right(&object->external);
}

float layout_get_external_width(const layout* object) {
    return dimension_get_width(&object->external);
}

float layout_get_external_center(const layout* object) {
    return dimension_get_center(&object->external);
}

/*
Actual dimensions- describes this object's position and size
as it should be rendered on screen.
*/
float layout_get_actual_top(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_top(&object->actual);
}

float layout_get_actual_bottom(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_bottom(&object->actual);
}

float layout_get_actual_height(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_height(&object->actual);
}

float layout_get_actual_middle(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_middle(&object->actual);
}

float layout_get_actual_left(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_left(&object->actual);
}

float layout_get_actual_right(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_right(&object->actual);
}

float layout_get_actual_width(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_width(&object->actual);
}

float layout_get_actual_center(layout* object) {
    layout_update_actual_dimensions(object);
    return dimension_get_center(&object->actual);
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

It is important to note that the internal coordinates are intended to be set
prior to adding children and setting their external coordinates.  Changeing
the internal coordinates after adding children can lead to unintended effects,
particularly if an axis has its coordinate system inverted (eg, when the old
coordinate system was increasing down the screen but the new coordinate system
is increasing up instead).  Children are not edited by an internal coordinate
change.

Additionally, internal coordinates may not produce a width or height of zero,
otherwise size resolution will fail!
*/
void layout_set_internal_top(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_top(&object->internal, value, priority);
}

void layout_set_internal_bottom(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_bottom(&object->internal, value, priority);
}

void layout_set_internal_height(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_height(&object->internal, value, priority);
}

void layout_set_internal_middle(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_middle(&object->internal, value, priority);
}

void layout_set_internal_left(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_left(&object->internal, value, priority);
}

void layout_set_internal_right(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_right(&object->internal, value, priority);
}

void layout_set_internal_width(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_width(&object->internal, value, priority);
}

void layout_set_internal_center(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_center(&object->internal, value, priority);
}

/*
External dimension manipulation
These functions change the external dimension values for this object.
The appropriate priorty flags are used to determine which values are
actually modified when setting a value.

The external coordinates provided depend and are relative to the parent
object's internal coordinate system.  Very specifically, the bounds of the
internal coordinate system for an object are the bounds specified by the
external coordinates for that object.  Additionally, the object must respect
the orientation of the parent's internal axes- if the parent's internal top
is less than its bottom, then the child's external top must also be less than
its bottom.  If a change would be made that violates this constraint, the
value is not changed.
*/
void layout_set_external_top(layout* object, const float value, const unsigned int priority) {
    //dimension* dimension = &object->external;
    //const float old_value = dimension_get_top(dimension);
    dimension_set_top(&object->external, value, priority);
    /*
    Commenting this out for now-
    the coder may consider an inverted top and bottom as as flip indicator.

    //If there is a parent AND the difference from the top and bottom of the
    //parent's internal bounds has a different sign as this object's internal
    //bounds, then reset it back to the old value.
    if (object->parent &&
      (layout_get_internal_top(object->parent) - layout_get_internal_bottom(object->parent)) *
      (value - dimension_get_bottom(dimension)) < 0) {
        dimension_set_top(dimension, old_value, priority);
        }
    */
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
}

void layout_set_external_bottom(layout* object, const float value, const unsigned int priority) {
    //dimension* dimension = &object->external;
    //const float old_value = dimension_get_bottom(dimension);
    dimension_set_bottom(&object->external, value, priority);

    /*
    Commenting this out for now-
    the coder may consider an inverted top and bottom as as flip indicator.

    //If there is a parent AND the difference from the top and bottom of the
    //parent's internal bounds has a different sign as this object's internal
    //bounds, then reset it back to the old value.
    if (object->parent &&
      (layout_get_internal_top(object->parent) - layout_get_internal_bottom(object->parent)) *
      (dimension_get_top(dimension) - value) < 0) {
        dimension_set_bottom(dimension, old_value, priority);
        }
    */
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
}

void layout_set_external_height(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_height(&object->external, value, priority);
}

void layout_set_external_middle(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_middle(&object->external, value, priority);
}

void layout_set_external_left(layout* object, const float value, const unsigned int priority) {
    //dimension* dimension = &object->external;
    //const float old_value = dimension_get_left(dimension);
    dimension_set_left(&object->external, value, priority);
    /*
    Commenting this out for now-
    the coder may consider an inverted top and bottom as as flip indicator.

    //If there is a parent AND the difference from the top and bottom of the
    //parent's internal bounds has a different sign as this object's internal
    //bounds, then reset it back to the old value.
    if (object->parent &&
      (layout_get_internal_left(object->parent) - layout_get_internal_right(object->parent)) *
      (value - dimension_get_right(dimension)) < 0) {
        dimension_set_left(dimension, old_value, priority);
        }
    */
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
}

void layout_set_external_right(layout* object, const float value, const unsigned int priority) {
    //dimension* dimension = &object->external;
    //const float old_value = dimension_get_right(dimension);
    dimension_set_right(&object->external, value, priority);
    /*
    Commenting this out for now-
    the coder may consider an inverted top and bottom as as flip indicator.

    //If there is a parent AND the difference from the top and bottom of the
    //parent's internal bounds has a different sign as this object's internal
    //bounds, then reset it back to the old value.
    if (object->parent &&
      (layout_get_internal_left(object->parent) - layout_get_internal_right(object->parent)) *
      (dimension_get_left(dimension)) - value < 0) {
        dimension_set_right(dimension, old_value, priority);
        }
    */
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
}

void layout_set_external_width(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_width(&object->external, value, priority);
}

void layout_set_external_center(layout* object, const float value, const unsigned int priority) {
    //Mark the object as dirty.
    object->flags |= LAYOUT_FLAG_DIRTY;
    dimension_set_center(&object->external, value, priority);
}


/*
Child Manipulation
Provides functions used to interface children objects with their parents.
*/
void attach_child(layout* parent, layout* child) {
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

/*
Basic Tree Walk
Provides ways to traverse a layout tree.  Recursive function.
*/
void walk_tree_depth_first(const layout* object, void (*callback)(const layout*)) {
    layout* index = object->children;;
    //Call the parent first.
    (*callback)(object);
    //Now call the children.
    while (index) {
        walk_tree_depth_first(index, callback);
    }
}

void walk_tree_width_first(const layout* object, void (*callback)(const layout*)) {
    layout* index = object->children;;
    //If this is the root node, call it first.
    if (!object->parent) (*callback)(object);
    //Now call the children.
    while (index) {
        (*callback)(index);
    }
    //Now recurse into the children the children.
    index = object->children;
    while (index) {
        walk_tree_width_first(index, callback);
    }
}

/*
Layout Arrays
Using a tree walk, create an array representation of the nodes. May be sorted.
*/
int get_node_count(const layout* object) {
    int count = 1;
    layout* index = object->children;;
    while(index) {
        count += get_node_count(index);
    }
    return count;
}

int generate_layout_list(const layout** list, const int offset, const layout* object) {
    int count = 1;
    layout* index = object->children;
    list[offset] = object;
    while (index) {
        count += generate_layout_list(list, offset + count, index);
    }
    return count;
}

const layout** get_layout_array(const layout* object) {
    int count = get_node_count(object);
    const layout** list = (const layout**) calloc(count, sizeof(layout*));
    generate_layout_list(list, 0, object);
    return list;
}

const layout** get_sorted_layout_array(const layout* object, int (*compare)(const void*, const void*)) {
    int count = get_node_count(object);
    const layout** list = (const layout**) calloc(count, sizeof(layout*));
    generate_layout_list(list, 0, object);
    qsort(list, count, sizeof(layout*), compare);
    return list;
}

void destroy_sorted_layout_array(layout* list) {
    free(list);
}

/*
Size resolution functions
These normalize the object's size relative to its parent.
*/

/*
This function is intended to calculate the external dimensions of object in
terms of the root layout object.  The resulting dimension expresses the size
of the object in terms of the external dimensions of the root layout object.
Assuming that the external dimensions of the root layout object is the
rendering location for the tree on the screen, the resutling dimension is the
actual rendering coordinates.

It assumes that the parent, if any, has correct actual dimensions.
*/

void layout_calculate_actual_dimensions(layout *object) {
    layout* parent = object->parent;
    if (parent) {
        object->actual = dimension_convert_coordinate_system(&object->external, &parent->internal, &parent->actual);
    } else {
        object->actual = object->external;
    }
}

void layout_update_actual_dimensions(layout* object) {
    if (object->parent) {
        layout_update_actual_dimensions(object->parent);
    }
    if (object->flags & LAYOUT_FLAG_DIRTY) {
        layout* index = children;

        object->flags ^= LAYOUT_FLAG_DIRTY;
        layout_calculate_actual_dimensions(object);

        //Since this was dirty, all children must be marked dirty.
        while (index) {
            index->flags |= LAYOUT_FLAG_DIRTY;
            index = index->next;
        }
    }
}
