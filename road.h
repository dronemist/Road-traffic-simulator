#ifndef __ROAD_H__
#define __ROAD_H__
class road
{
private:
    int road_id;
    int road_length;
    int road_width;
    int road_signal;
    bool light_signal; // false for red, true for green
public:
    road(int,int,int,int,bool);
    road();
    int getWidth();
    int getLength();
    int getId();
    int getSignal();
    bool getLightSignal();
    void setLightSignal(bool);
};
#endif