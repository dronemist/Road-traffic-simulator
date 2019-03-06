#ifndef __CARS_H__
#define __CARS_H__
#include <string>
#include "Vehicles.h"
class car: public vehicles
{
public:
    car(int=2, int=2, int=-1, int=0, float=5.0f, float=1.0f);
};
#endif