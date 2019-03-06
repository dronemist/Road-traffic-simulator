#include <iostream>
#include "Vehicles.h"
#include "Car.h"

car::car(int length, int width, int x , int y ,float max_speed , float max_acceleration)
{
    vehicle_type = "Car";
    vehicle_length = length;
    vehicle_width = width;
    vehicle_max_speed = max_speed;
    vehicle_curr_speed = 0;
    x_coordinate_start = x;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;
    y_coordinate_start = y;
    y_coordinate_end = y_coordinate_start + vehicle_width - 1;
    vehicle_max_acceleration = max_acceleration;
}
