#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "dimension.h"

#define LAYOUT_TOP      AXIS_MINIMAL
#define LAYOUT_MIDDLE   AXIS_MEDIAN
#define LAYOUT_BOTTOM   AXIS_MAXIMAL
#define LAYOUT_HEIGHT   AXIS_LENGTH

#define LAYOUT_LEFT     AXIS_MINIMAL
#define LAYOUT_CENTER   AXIS_MEDIAN
#define LAYOUT_RIGHT    AXIS_MAXIMAL
#define LAYOUT_WIDTH    AXIS_LENGTH

//Indicates that the actual coordinates need to be recalculated.
#define LAYOUT_FLAG_DIRTY       (1<< 0)

typedef struct layout layout;

struct layout{
    /*
    Coordinates that describe where this object is in relation to it's parent
    */
    dimension external;
    /*
    Coordinates that describe where this object's children are in relation to
    itself.
    */
    dimension internal;
    /*
    Coordinates that describe where this object is in relation to the root
    layout object's external coordinates.  In other words, this is the
    coordinates to directly render onto the screen with.
    */
    dimension actual;

    // This object has flags.  Yay.
    unsigned long int flags;

    // This object is a singly linked list and tree node.
    layout* parent;
    layout* next;
    layout* children;

    // There is some external renderable associated with this layout object.
    void* renderable;
};

/*
Base memory management functions.
*/
layout* layout_create(void);
void layout_delete(layout* object);

/*
Internal dimensions- describes this object's internal coordinate system.
Child objects are positioned relatively based on these parameters.
*/
float layout_get_internal_top(const layout* object);
float layout_get_internal_bottom(const layout* object);
float layout_get_internal_height(const layout* object);
float layout_get_internal_middle(const layout* object);
float layout_get_internal_left(const layout* object);
float layout_get_internal_right(const layout* object);
float layout_get_internal_width(const layout* object);
float layout_get_internal_center(const layout* object);

/*
External dimensions- describes this object's position and size
relative to its parent's coordinate system
*/
float layout_get_external_top(const layout* object);
float layout_get_external_bottom(const layout* object);
float layout_get_external_height(const layout* object);
float layout_get_external_middle(const layout* object);
float layout_get_external_left(const layout* object);
float layout_get_external_right(const layout* object);
float layout_get_external_width(const layout* object);
float layout_get_external_center(const layout* object);
/*
Actual dimensions- describes this object's position and size
as it should be rendered on screen.
*/
float layout_get_actual_top(layout* object);
float layout_get_actual_bottom(layout* object);
float layout_get_actual_height(layout* object);
float layout_get_actual_middle(layout* object);
float layout_get_actual_left(layout* object);
float layout_get_actual_right(layout* object);
float layout_get_actual_width(layout* object);
float layout_get_actual_center(layout* object);

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
void layout_set_internal_top(layout* object, const float value, const unsigned int priority);
void layout_set_internal_bottom(layout* object, const float value, const unsigned int priority);
void layout_set_internal_height(layout* object, const float value, const unsigned int priority);
void layout_set_internal_middle(layout* object, const float value, const unsigned int priority);
void layout_set_internal_left(layout* object, const float value, const unsigned int priority);
void layout_set_internal_right(layout* object, const float value, const unsigned int priority);
void layout_set_internal_width(layout* object, const float value, const unsigned int priority);
void layout_set_internal_center(layout* object, const float value, const unsigned int priority);

/*
External dimension manipulation
These functions change the external dimension values for this object.
The appropriate priorty flags are used to determine which values are
actually modified when setting a value.

The external coordinates provided depend and are relative to the parent
object's internal coordinate system.  Very specifically, the bounds of the
internal coordinate system for an object are the bounds specified by the
external coordinates for that object.

**NOTE: This has been receinded- a child with a top that would be rendered
below its bottom may be used by the coder as a flip indicator.

Additionally, the object must respect
the orientation of the parent's internal axes- if the parent's internal top
is less than its bottom, then the child's external top must also be less than
its bottom.  If a change would be made that violates this constraint, the
value is not changed.
*/
void layout_set_external_top(layout* object, const float value, const unsigned int priority);
void layout_set_external_bottom(layout* object, const float value, const unsigned int priority);
void layout_set_external_height(layout* object, const float value, const unsigned int priority);
void layout_set_external_middle(layout* object, const float value, const unsigned int priority);
void layout_set_external_left(layout* object, const float value, const unsigned int priority);
void layout_set_external_right(layout* object, const float value, const unsigned int priority);
void layout_set_external_width(layout* object, const float value, const unsigned int priority);
void layout_set_external_center(layout* object, const float value, const unsigned int priority);

/*
Child Manipulation
Provides functions used to interface children objects with their parents.
*/
void attach_child(layout* parent, layout* child);
void detach_child(layout* parent, layout* child);

/*
Basic Tree Walk
Provides ways to traverse a layout tree.  Recursive function.
*/
void walk_tree_depth_first(const layout* object, void (*callback)(const layout*));
void walk_tree_width_first(const layout* object, void (*callback)(const layout*));

/*
Layout Arrays
Using a tree walk, create an array representation of the nodes. May be sorted.
*/
int get_node_count(const layout* object);
int generate_layout_list(const layout** list, const int offset, const layout* object);
const layout** get_layout_array(const layout* object);
const layout** get_sorted_layout_array(const layout* object, int (*compare)(const void*, const void*));
void destroy_sorted_layout_array(layout* list);

/*
Size resolution functions
These normalize the object's size relative to its parent.
*/
void layout_calculate_actual_dimensions(layout *object);
void layout_update_actual_dimensions(layout* object);

#endif // __LAYOUT_H__
