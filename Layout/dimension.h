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

float get_top(dimension* object);
float get_bottom(dimension* object);
float get_height(dimension* object);
float get_middle(dimension* object);
float get_left(dimension* object);
float get_right(dimension* object);
float get_width(dimension* object);
float get_center(dimension* object);

void set_top(dimension* object, float value, unsigned int priority);
void set_bottom(dimension* object, float value, unsigned int priority);
void set_height(dimension* object, float value, unsigned int priority);
void set_middle(dimension* object, float value, unsigned int priority);
void set_left(dimension* object, float value, unsigned int priority);
void set_right(dimension* object, float value, unsigned int priority);
void set_width(dimension* object, float value, unsigned int priority);
void set_center(dimension* object, float value, unsigned int priority);

#endif // __DIMENSION_H__
