#include <iostream>
#include <string>
#include "road.h"

// Constructor for road class
road::road(int id,int length, int width, int signal,bool colour_of_signal)
{
    road_id = id;
    road_length = length;
    road_width = width;
    road_signal = signal;
    light_signal = colour_of_signal;
}
road::road()
{
    road_id = 0;
    road_length = 0;
    road_width = 0;
    road_signal = 0;
    light_signal = false;
}
int road::getLength()
{
    return road_length;
}
int road::getWidth()
{
    return road_width;
}
int road::getId()
{
    return road_id;
}
int road::getSignal()
{
    return road_signal;
}
bool road::getLightSignal()
{
    return light_signal;
}
void road::setLightSignal(bool colour_of_signal)
{
    light_signal = colour_of_signal;
}

