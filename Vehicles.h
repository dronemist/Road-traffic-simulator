#ifndef __VEHICLES_H__
#define __VEHICLES_H__
#include<string>
class vehicles
{
protected:
    std::string vehicle_type;
    std::string vehicle_colour;
    int vehicle_length;
    int vehicle_width;
    int x_coordinate_start; // starting x_coordinate
    int y_coordinate_start; // starting y_coordinate
    int x_coordinate_end; // ending x_coordinate
    int y_coordinate_end; // ending y_coordinate
    float vehicle_max_speed;
    float vehicle_curr_speed;
    float vehicle_def_speed; // the initial speed of the vehicle when added
    float vehicle_max_acceleration;
    float vehicle_max_deceleration;
    bool is_accelerating;
public:
 vehicles(std::string,std::string,int=2, int=2, int=-1, int=0, float=5.0f, float=1.0f,float = 1);
 vehicles();
 int getXcoordinateStart();
 int getYcoordinateStart();
 int getXcoordinateEnd();
 int getYcoordinateEnd();
 char getRepresentation(); // function to get the representation of the vehicle in the simulation
 int getLength();
 int getWidth();
 float getCurrSpeed();
 float getDefCurrSpeed();
 bool getIsAccelerating();
 void updateXcoordinate(int, bool);
 void setYcoordinate(int);
 void setXcoordinate(int);
 void setCurrSpeed(int);
};
#endif