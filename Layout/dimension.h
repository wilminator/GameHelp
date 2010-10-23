#ifndef __DIMENSION_H__
#define __DIMENSION_H__

#define AXIS_MINIMAL    1
#define AXIS_MEDIAN     2
#define AXIS_MAXIMAL    3
#define AXIS_LENGTH     4

struct axis {
    float minimal;
    float maximal;
};

typedef struct axis axis;

/*
Internal functions
float axis_get_minimal(axis* object);
float axis_get_maximal(axis* object);
float axis_get_length(axis* object);
float axis_get_midian(axis* object);
void axis_set_minimal(axis* object, float value, unsigned int priority = AXIS_LENGTH);
void axis_set_maximal(axis* object, float value, unsigned int priority = AXIS_LENGTH);
void axis_set_length(axis* object, float value, unsigned int priority = AXIS_MEDIAN);
void axis_set_median(axis* object, float value, unsigned int priority = AXIS_LENGTH);
*/

struct dimension {
    axis horizontal;
    axis vertical;
};

typedef struct dimension dimension;

const float dimension_get_top(const dimension* object);
const float dimension_get_bottom(const dimension* object);
const float dimension_get_height(const dimension* object);
const float dimension_get_middle(const dimension* object);
const float dimension_get_left(const dimension* object);
const float dimension_get_right(const dimension* object);
const float dimension_get_width(const dimension* object);
const float dimension_get_center(const dimension* object);

void dimension_set_top(dimension* object, const float value, const unsigned int priority);
void dimension_set_bottom(dimension* object, const float value, const unsigned int priority);
void dimension_set_height(dimension* object, const float value, const unsigned int priority);
void dimension_set_middle(dimension* object, const float value, const unsigned int priority);
void dimension_set_left(dimension* object, const float value, const unsigned int priority);
void dimension_set_right(dimension* object, const float value, const unsigned int priority);
void dimension_set_width(dimension* object, const float value, const unsigned int priority);
void dimension_set_center(dimension* object, const float value, const unsigned int priority);
/* Size resolution functions */
dimension dimension_convert_coordinate_system(dimension* child_external, dimension* parent_internal, dimension* parent_actual);

#endif // __DIMENSION_H__
