#ifndef KALMAN_H
#define KALMAN_H

#include <BasicLinearAlgebra.h>

// data type to hold the filtered value
struct FilteredValues{
    float x_accel_filtered;
    float y_accel_filtered;
} ;

// kalmanUpdate This filters our altitude and acceleration values
struct FilteredValues kalmanUpdate(float altitude, float acceleration);

#endif