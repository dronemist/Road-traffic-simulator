#include <iostream>
#include <string>
#include "Vehicles.h"

// See how to provide default values
vehicles::vehicles(std::string type, int length = 2, int width = 2, int x = 0, int y = 0 ,float max_speed = 1.0f, float max_acceleration = 0.0f)
{
    vehicle_type = type;
    vehicle_length = length;
    vehicle_width = width;
    vehicle_max_speed = max_speed;
    x_coordinate_start = x;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;
    y_coordinate_start = y;
    y_coordinate_end = y_coordinate_start + vehicle_width - 1;
    vehicle_max_acceleration = max_acceleration;
}
vehicles::vehicles()
{
    vehicle_type = "Car";
    vehicle_length = 0;
    vehicle_width = 0;
    vehicle_max_speed = 0;
    vehicle_max_acceleration = 0;
    x_coordinate_start = 0;
    y_coordinate_start = 0;
    x_coordinate_end = 0;
    y_coordinate_end = 0;
}
int vehicles::getXcoordinateStart()
{
    return x_coordinate_start;
}
int vehicles::getYcoordinateStart()
{
    return y_coordinate_start;
}
int vehicles::getXcoordinateEnd()
{
    return x_coordinate_end;
}
int vehicles::getYcoordinateEnd()
{
    return y_coordinate_end;
}
int vehicles::getWidth()
{
    return vehicle_width;
}
void vehicles::setXcoordinate(int signal,bool colour_of_signal)
{
    // x_coordinate of a vehicle updated after 1 sec
    /*
        signal: the x_coordinate of the signal
        colour_of_signal: the colour of signal
    */
    if(x_coordinate_start != signal || colour_of_signal == true)
        x_coordinate_start += vehicle_max_speed + (0.5)*vehicle_max_acceleration;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;    
}
char vehicles::getRepresentation()
{
    // Each vehicle is represented by the first character of its string
    return vehicle_type[0];
}