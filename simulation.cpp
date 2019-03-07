#include <iostream>
#include <vector>
#include <unistd.h>
#include "road.h"
#include "Vehicles.h"
#include "simulation.h"
// defining sec_1 as 10^6 microseconds
const long sec_1 = 1000000;
simulation::simulation(road def_road,std::vector<vehicles> &def_vehicles)
{
    id = def_road.getId();
    sim_road = def_road;
    sim_vehicles = def_vehicles;
    // initialising sim_map to the dimensions of the road 
    sim_map = std::vector<std::vector<int>> 
    (sim_road.getWidth(),std::vector<int> (sim_road.getLength(),0));
}
simulation::simulation()
{
    road r;
    vehicles v;
    sim_road = r;
    sim_vehicles = std::vector<vehicles>(0,v);
    sim_map = std::vector<std::vector<int>> 
    (sim_road.getWidth(),std::vector<int> (sim_road.getLength(),0));
}
void simulation::setRoad(road r)
{
    sim_road = r;
    sim_map = std::vector<std::vector<int>> 
    (sim_road.getWidth(),std::vector<int> (sim_road.getLength(),0));
    id = r.getId();
}
void simulation::setVehicles(std::vector<vehicles> &v)
{
    sim_vehicles = v;
}
void simulation::setSignal(bool signal)
{
    sim_road.setLightSignal(signal);
}
void simulation::addVehicle(vehicles v)
{
    sim_vehicles.push_back(v);
}
void simulation::deleteVehicle(int index)
{
    // index: index of vector to be removed
    sim_vehicles.erase(sim_vehicles.begin()+index);
}
void simulation::setZero(int index)
{
    // Sets the map elements to zero for the vehicle at index to be positioned on the map
    for(int i=0;i<sim_road.getWidth();i++)
    {
        for(int j=0;j<sim_road.getLength();j++)
        {
            if(sim_map.at(i).at(j) > index)
                    sim_map.at(i).at(j) = 0; 
            if (j==sim_road.getSignal()-1 && sim_road.getLightSignal()==false)
                sim_map.at(i).at(j) = -1;
            if (j==sim_road.getSignal()-1 && sim_road.getLightSignal()==true && sim_map.at(i).at(j)==-1)
                sim_map.at(i).at(j) = 0;  
        }
    }
}
void simulation::positionVehicle(int index)
{
    // Function to position the vehicle at index on the sim_map
    int minimum = sim_vehicles.at(index).getXcoordinateStart();
    for(int i = sim_vehicles.at(index).getYcoordinateStart();i <= sim_vehicles.at(index).getYcoordinateEnd(); i++)
    {
        for(int j = 0;j <= std::min(sim_vehicles.at(index).getXcoordinateStart(),sim_road.getLength()-1);j++)
        {
            if(sim_map.at(i).at(j) < index+1 && sim_map.at(i).at(j)>0)
            {
                // checking if any of the previous vehicles is in front of the current vehicle
                if(j <= minimum)
                {
                    sim_vehicles.at(index).setXcoordinate(j-1);
                    minimum = j-1;
                    sim_vehicles.at(index).setCurrSpeed(std::min(sim_vehicles.at(sim_map.at(i).at(j)).getCurrSpeed(),sim_vehicles.at(index).getCurrSpeed()));
                }
            }
        }
    }
    for(int i=std::max(0,sim_vehicles.at(index).getYcoordinateStart());i <= std::min(sim_road.getWidth()-1,sim_vehicles.at(index).getYcoordinateEnd());i++)
        for(int j=std::max(0,sim_vehicles.at(index).getXcoordinateEnd());j <= std::min(sim_road.getLength()-1,sim_vehicles.at(index).getXcoordinateStart());j++)
                sim_map.at(i).at(j) = index+1;
}
bool simulation::canBeAdded(vehicles v)
{
    for(int i=v.getYcoordinateStart();i<=v.getYcoordinateEnd();i++)
    {
        if(sim_map.at(i).at(0) > 0 && sim_map.at(i).at(0) < sim_vehicles.size()+1)
            return false;
    }
    return true;
}
void simulation::printMap()
{
        for(int i=0;i<sim_road.getWidth();i++)
        {
            for(int j=0;j<sim_road.getLength();j++)
            {
                int temp = sim_map.at(i).at(j); 
                if(temp>0)
                    {
                        std::cout<<sim_vehicles.at(temp-1).getRepresentation();
                    }
                else if (temp == -1)
                {
                    std::cout<<"|";
                }
                else
                    std::cout<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
}
void simulation::updateXcoordinates()
{
    // function to update X coordinates of all the vehicles to their maximum possible values
    for(int k=0;k<sim_vehicles.size();k++)    
        sim_vehicles.at(k).updateXcoordinate(sim_road.getSignal()-1,sim_road.getLightSignal());  
}
void simulation::runSimulation(std::vector<vehicles> &v,std::vector<int> &add_time,bool till_end,int start_time,int end_time = -1)
{
    // run simulation from start_time to end_time
    // v represents the vector of vehicles to be added, added one per second
    //add_time is a vector which signifies the times at which vehicles are added
    int cnt = start_time;
    while( cnt <= end_time || (till_end == true && (v.size() > 0 || sim_vehicles.size()>0)))
    { 
        if(v.size() > 0
        && cnt >= add_time.at(0)
        && canBeAdded(v.at(0)))
        {
            addVehicle(v.at(0));
            v.erase(v.begin());
            add_time.erase(add_time.begin());
        }
        for(int k = 0;k < sim_vehicles.size();k++)
        {
            setZero(k);
            positionVehicle(k);
        }
        std::cout<<"Time: "<<cnt<<std::endl;
        printMap();
        // Removing vehicles that have left the road
        for(int k = 0;k < sim_vehicles.size();k++)
        {    
            if(sim_vehicles.at(k).getXcoordinateEnd() >= sim_road.getLength())
                {    
                    deleteVehicle(k);
                    k--;
                }       
        }           
        // adding vehicles according to the time
        cnt++;
        updateXcoordinates(); 
        usleep(sec_1);
    }
}
// int main(int argc, char const *argv[])
// {
//     road r1(1,10,4,15,true);
//     std::vector<vehicles> v;
//     std::vector<int> t;
//     t.push_back(1);
//     t.push_back(2);
//    // t.push_back(3);
//     simulation s(r1,v);
//     vehicles v2("Truck","",3,3,0,1,1,1);
//     vehicles v1("Car","",2,2,0,2,1,1);
//     vehicles v3("bike","",1,1,0,0,1,1);
//     v.push_back(v1);
//     v.push_back(v3);
//     //v.push_back(v2);
//     s.runSimulation(v,t,true,0);
//     v.push_back(v3);
//     t.push_back(22);
//     // s.setSignal(true);
//     // s.runSimulation(v,t,true,21);
//     return 0;
// }
