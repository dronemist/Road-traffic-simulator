#ifndef __SIMULATION_H__
#define __SIMULATION_H__
#include<vector>
#include <GLFW/glfw3.h>
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
    void setRoad(road);
    void setVehicles(std::vector<vehicles>&);
    int getNumberOfVehicles();
    void addVehicle(vehicles);
    void deleteVehicle(int);
    bool canBeAdded(vehicles);
    void setZero(int);
    void positionVehicle(int,std::vector<std::vector<int>>);
    void printMap();
    void updateXcoordinates();
    void runSimulation(std::vector<vehicles> &,std::vector<int> &,bool,int,GLFWwindow* window,int=-1);
    void setSignal(bool);
    void rearrangeVehicles();
    int canOvertake(vehicles,vehicles,int);
    bool checkRight(std::vector<std::vector<int>>,int,int);
    bool checkLeft(std::vector<std::vector<int>>,int,int);
    bool checkEnd(int);
    bool checkIfVehiclePresent(int x,int y,int index);
    std::vector<vehicles> getSimVehicles();

};
#endif