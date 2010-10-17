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
float get_minimal(axis* object);
float get_maximal(axis* object);
float get_length(axis* object);
float get_midian(axis* object);
void set_minimal(axis* object, float value, unsigned int priority = AXIS_LENGTH);
void set_maximal(axis* object, float value, unsigned int priority = AXIS_LENGTH);
void set_length(axis* object, float value, unsigned int priority = AXIS_MEDIAN);
void set_median(axis* object, float value, unsigned int priority = AXIS_LENGTH);
*/

struct dimension {
    axis horizontal;
    axis vertical;
};

typedef struct dimension dimension;

const float get_top(const dimension* object);
const float get_bottom(const dimension* object);
const float get_height(const dimension* object);
const float get_middle(const dimension* object);
const float get_left(const dimension* object);
const float get_right(const dimension* object);
const float get_width(const dimension* object);
const float get_center(const dimension* object);

void set_top(dimension* object, const float value, const unsigned int priority);
void set_bottom(dimension* object, const float value, const unsigned int priority);
void set_height(dimension* object, const float value, const unsigned int priority);
void set_middle(dimension* object, const float value, const unsigned int priority);
void set_left(dimension* object, const float value, const unsigned int priority);
void set_right(dimension* object, const float value, const unsigned int priority);
void set_width(dimension* object, const float value, const unsigned int priority);
void set_center(dimension* object, const float value, const unsigned int priority);

#endif // __DIMENSION_H__
