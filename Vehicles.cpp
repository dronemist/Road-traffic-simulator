#include <iostream>
#include <string>
#include <cmath>
#include "Vehicles.h"

// The type needs to be specified but others may not be specified and defaulted as given in the header file
vehicles::vehicles(std::string type,std::string colour, int length, int width, int x , int y ,float max_speed , float max_acceleration,float curr_speed)
{
    if(curr_speed >= max_speed)
        is_accelerating = false;
    else
        is_accelerating = true;
    curr_speed = std::min(curr_speed,max_speed);
    vehicle_type = type;
    vehicle_colour = colour;
    vehicle_length = length;
    vehicle_width = width;
    vehicle_max_speed = max_speed;
    vehicle_curr_speed = curr_speed;
    vehicle_def_speed = curr_speed;
    x_coordinate_start = x;
    x_coordinate_end = x_coordinate_start - vehicle_length + 1;
    y_coordinate_start = y;
    y_coordinate_end = y_coordinate_start + vehicle_width - 1;
    vehicle_max_acceleration = max_acceleration;
}
//The no argument constructor
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
//returns the x coordinate of the front of the vehicle
int vehicles::getXcoordinateStart()
{
    return x_coordinate_start;
}

//returns the upper y coordinate of the vehicle
int vehicles::getYcoordinateStart()
{
    return y_coordinate_start;
}

//returns the X coordinate of the back of the vehicle
int vehicles::getXcoordinateEnd()
{
    return x_coordinate_end;
}

//returns the lower Y coordinate of vehicle
int vehicles::getYcoordinateEnd()
{
    return y_coordinate_end;
}

//returns the width of the vehicle
int vehicles::getWidth()
{
    return vehicle_width;
}

//returns the current speed of the vehicle
float vehicles::getCurrSpeed()
{
    return vehicle_curr_speed;
}

//updates position of the vehicle according to Newton's Laws of Motion
void vehicles::updateXcoordinate(int signal,bool colour_of_signal)
{
    // x_coordinate of a vehicle updated after 1 sec
    /*
        signal: the x_coordinate of the signal
        colour_of_signal: the colour of signal
    */
    if(vehicle_curr_speed == vehicle_max_speed)
        is_accelerating = false;
    else
        is_accelerating = true;    
    if(colour_of_signal == true || x_coordinate_start >= signal)
    {
        // if signal is green keep the vehicle going
        if(is_accelerating)
        {   
            x_coordinate_start += vehicle_curr_speed + (0.5)*vehicle_max_acceleration;    
            vehicle_curr_speed += vehicle_max_acceleration;
            vehicle_curr_speed = std::min(vehicle_curr_speed,vehicle_max_speed);
        }
        else
        {
            x_coordinate_start += vehicle_curr_speed;
        }
    }
    // signal-1 is done because vehicle has to stop just before the signal 
    else if(x_coordinate_start <= signal-1 && colour_of_signal == false)
    {
        // if signal is red the vehicle cannot cross the signal
        if(is_accelerating)
        {
            x_coordinate_start = std::min(int(floor(x_coordinate_start+
                                    vehicle_curr_speed + (0.5)*vehicle_max_acceleration)),signal-1);
            vehicle_curr_speed += vehicle_max_acceleration;
            vehicle_curr_speed = std::min(vehicle_curr_speed,vehicle_max_speed);
        }
        else
        {
            x_coordinate_start = std::min(int(x_coordinate_start+
                                    vehicle_curr_speed),signal-1);
        }
        
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
bool vehicles::getIsAccelerating()
{
    return is_accelerating;
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
float vehicles::getDefCurrSpeed()
{
    return vehicle_def_speed;
}