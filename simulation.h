#ifndef __SIMULATION_H__
#define __SIMULATION_H__
#include<vector>
#include "road.h"
#include "Vehicles.h"
class simulation
{
private:
    int id;
    road sim_road; // road for this simulation
    std::vector<vehicles> sim_vehicles; // vehicles present at a particular time in the simulation
    std::vector<std::vector<int>> sim_map;

public:
    simulation(road, std::vector<vehicles>&);
    simulation();
    void addVehicle(vehicles);
    void deleteVehicle(int);
    void setZero(int);
    void positionVehicle(int);
    void printMap();
    void updateXcoordinates();
    void runSimulation(int ,std::vector<vehicles> &);
    void setSignal(bool);
};
#endif