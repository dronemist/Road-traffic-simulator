#include <iostream>
#include <string>
#include <cmath>
#include "Vehicles.h"

// See how to provide default values
vehicles::vehicles(std::string type, int length = 2, int width = 2, int x = -1, int y = 0 ,float max_speed = 2.0f, float max_acceleration = 1.0f)
{
    vehicle_type = type;
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
vehicles::vehicles()
{
    vehicle_type = "Car";
    vehicle_length = 2;
    vehicle_width = 2;
    vehicle_max_speed = 2.0f;
    vehicle_max_acceleration = 1.0f;
    x_coordinate_start = -1;
    y_coordinate_start = 0;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;
    y_coordinate_end = y_coordinate_start + vehicle_width - 1;
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
float vehicles::getCurrSpeed()
{
    return vehicle_curr_speed;
}
void vehicles::updateXcoordinate(int signal,bool colour_of_signal)
{
    // x_coordinate of a vehicle updated after 1 sec
    /*
        signal: the x_coordinate of the signal
        colour_of_signal: the colour of signal
    */
    if(colour_of_signal == true || x_coordinate_start >= signal)
    {
        // if signal is green keep the vehicle going
        x_coordinate_start += vehicle_curr_speed + (0.5)*vehicle_max_acceleration;
        vehicle_curr_speed += vehicle_max_acceleration;
        vehicle_curr_speed = std::min(vehicle_curr_speed,vehicle_max_speed);
    }
    // signal-1 is done because vehicle has to stop just before the signal 
    else if(x_coordinate_start <= signal-1 && colour_of_signal == false)
    {
        // if signal is red the vehicle cannot cross the signal
        x_coordinate_start = std::min(int(floor(x_coordinate_start+
                                vehicle_curr_speed + (0.5)*vehicle_max_acceleration)),signal-1);
        vehicle_curr_speed += vehicle_max_acceleration;
        vehicle_curr_speed = std::min(vehicle_curr_speed,vehicle_max_speed);
    }
    if(x_coordinate_start == signal-1 && colour_of_signal == false)
        // the vehicle is supposed to stop at red signal
        vehicle_curr_speed = 0;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;    
}
void vehicles::setXcoordinate(int x)
{
    x_coordinate_start = x;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;
}
void vehicles::setYcoordinate(int y)
{
    y_coordinate_start = y;
    y_coordinate_end = y_coordinate_start + vehicle_width - 1;
}
void vehicles::setCurrSpeed(int speed)
{
    vehicle_curr_speed = speed;
}
char vehicles::getRepresentation()
{
    // Each vehicle is represented by the first character of its string
    return vehicle_type[0];
}