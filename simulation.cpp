/*
Notes(to be deleted before submitting)
sim_map -> array or vector
*/
#include <iostream>
#include <vector>
#include "road.h"
#include "Vehicles.h"
class simulation
{
private:
    int id;
    road sim_road; // road for this simulation
    std::vector<vehicles> sim_vehicles; // vehicles present at a particular time in the simulation
    std::vector<std::vector<char>> sim_map;

public:
    simulation(road, std::vector<vehicles>&);
    simulation();
    void add_vehicle(vehicles v);
};
simulation::simulation(road def_road,std::vector<vehicles> &def_vehicles)
{
    id = def_road.getId();
    sim_road = def_road;
    sim_vehicles = def_vehicles;
    // initialising sim_map to the dimensions of the road 
    sim_map = std::vector<std::vector<char>> 
    (sim_road.getWidth(),std::vector<char> (sim_road.getLength(),' '));
}
simulation::simulation()
{
    road r;
    vehicles v;
    sim_road = r;
    sim_vehicles = std::vector<vehicles>(0,v);
    sim_map = std::vector<std::vector<char>> 
    (sim_road.getWidth(),std::vector<char> (sim_road.getLength(),' '));
}
void simulation::add_vehicle(vehicles v)
{
    sim_vehicles.push_back(v);
}
int main(int argc, char const *argv[])
{
    road r1;
    return 0;
}
