#ifndef __VEHICLES_H__
#define __VEHICLES_H__
#include<string>
class vehicles
{
protected:
    std::string vehicle_type;
    int vehicle_length;
    int vehicle_width;
    int x_coordinate_start; // starting x_coordinate
    int y_coordinate_start; // starting y_coordinate
    int x_coordinate_end; // ending x_coordinate
    int y_coordinate_end; // ending y_coordinate
    float vehicle_max_speed;
    float vehicle_curr_speed;
    float vehicle_max_acceleration;
public:
 vehicles(std::string, int, int, int, int, float, float);
 vehicles();
 int getXcoordinateStart();
 int getYcoordinateStart();
 int getXcoordinateEnd();
 int getYcoordinateEnd();
 char getRepresentation(); // function to get the representation of the vehicle in the simulation
 int getLength();
 int getWidth();
 float getCurrSpeed();
 void updateXcoordinate(int, bool);
 void setYcoordinate(int);
 void setXcoordinate(int);
 void setCurrSpeed(int);
};
#endif