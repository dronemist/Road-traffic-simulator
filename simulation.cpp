#include <iostream>
#include <vector>
#include <unistd.h>
#include <cmath>
#include <string>
#include <GLFW/glfw3.h>
#include "road.h"
#include "Vehicles.h"
#include "simulation.h"
#include <algorithm>
// defining sec_1 as 10^6 microseconds

const long sec_1 = 1000000;
// void (simulation::*disp)(void) = &simulation::display;
// void (simulation::*resh)(int,int) = &simulation::reshape;

bool compare(vehicles v1,vehicles v2)
{
    return v1.getXcoordinateStart() > v2.getXcoordinateStart();
}

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
int simulation::canOvertake(vehicles back,vehicles front,int index)
{
    int right = 1,left = 1;
    if(front.getYcoordinateEnd() + back.getWidth() >= sim_road.getWidth())
        right = 0;
    else
    {
        for(int i = front.getYcoordinateEnd() + 1; i <= front.getYcoordinateEnd() + back.getWidth(); i++)
        {
            for(int j = 0; j <= std::min(back.getXcoordinateStart(),sim_road.getLength()-1);j++)
            {
                if(sim_map.at(i).at(j) < index+1 && sim_map.at(i).at(j) > 0)
                {
                    // a vehicle is already present
                    right = 0;
                    break;
                }
            }
            if(right == 0)
                break;
        }
    }
    if(front.getYcoordinateStart() - back.getWidth() < 0)
        left = 0;
    else
    {   
        
        for(int i = front.getYcoordinateStart() - 1; i >= front.getYcoordinateStart() - back.getWidth(); i--)
        {
            for(int j = 0; j <= std::min(back.getXcoordinateStart(),sim_road.getLength()-1);j++)
            {
                if(sim_map.at(i).at(j) < index+1 && sim_map.at(i).at(j) > 0)
                {
                    // a vehicle is already present
                    left = 0;
                    break;
                }
            }
            if(left == 0)
                break;
        } 
    }
    if(right == 1)
        return 1;
    else if(left == 1)
        return -1;
    else
    {
        return 0;
    }
            
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
    // Vector of vehicles because more than 1 vehicle may be collectively blocking the back vehicle
    std::vector<vehicles> up_front_vector;
    vehicles upFront;
    int flag = 0;
    for(int i = sim_vehicles.at(index).getYcoordinateStart();i <= sim_vehicles.at(index).getYcoordinateEnd(); i++)
    {
        for(int j = 0;j <= std::min(sim_vehicles.at(index).getXcoordinateStart(),sim_road.getLength()-1);j++)
        {
            if(sim_map.at(i).at(j) < index+1 && sim_map.at(i).at(j)>0)
            {
                // checking if any of the previous vehicles is in front of the current vehicle
                if(j <= minimum)
                {
                    if(j==minimum)    
                        up_front_vector.push_back(sim_vehicles.at(sim_map.at(i).at(j)-1));
                    else
                    {
                        up_front_vector.clear();
                        up_front_vector.push_back(sim_vehicles.at(sim_map.at(i).at(j)-1));
                    }
                    minimum = j;   
                    flag = 1; 
                }
            }
        }
    }
    if(flag == 1)
    {
        upFront = up_front_vector.at(0);
        int temp = canOvertake(sim_vehicles.at(index),upFront,index);
        for(int i = 0;i < up_front_vector.size();i++)
        {
           int temp2 = canOvertake(sim_vehicles.at(index),up_front_vector.at(i),index);
           if( temp2 != 0)
                {
                    upFront = up_front_vector.at(i);
                    temp = temp2;
                    break;
                } 
        }
        if(temp == 1)
        {
            sim_vehicles.at(index).setXcoordinate(upFront.getXcoordinateEnd() - 1);
            sim_vehicles.at(index).setYcoordinate(sim_vehicles.at(index).getYcoordinateStart() + 1);
            sim_vehicles.at(index).setCurrSpeed(std::min(upFront.getCurrSpeed(),sim_vehicles.at(index).getCurrSpeed()));
        }
        else if (temp == -1)
        {
            sim_vehicles.at(index).setXcoordinate(upFront.getXcoordinateEnd() - 1);
            sim_vehicles.at(index).setYcoordinate(sim_vehicles.at(index).getYcoordinateStart() - 1);
            sim_vehicles.at(index).setCurrSpeed(std::min(upFront.getCurrSpeed(),sim_vehicles.at(index).getCurrSpeed()));
        }
        else
        {
            sim_vehicles.at(index).setXcoordinate(upFront.getXcoordinateEnd() - 1);
            sim_vehicles.at(index).setCurrSpeed(std::min(upFront.getCurrSpeed(),sim_vehicles.at(index).getCurrSpeed()));
        }
    }   
    for(int i=std::max(0,sim_vehicles.at(index).getYcoordinateStart());i <= std::min(sim_road.getWidth()-1,sim_vehicles.at(index).getYcoordinateEnd());i++)
        for(int j=std::max(0,sim_vehicles.at(index).getXcoordinateEnd());j <= std::min(sim_road.getLength()-1,sim_vehicles.at(index).getXcoordinateStart());j++)
                sim_map.at(i).at(j) = index+1;
}
// Checking if a vehicle can be added to the simulation
bool simulation::canBeAdded(vehicles v)
{
    for(int i = v.getYcoordinateStart();i <= v.getYcoordinateEnd();i++)
    {
        if(sim_map.at(i).at(0) > 0 && sim_map.at(i).at(0) < sim_vehicles.size()+1)
            return false;
    }
    return true;
}
// function to printmap to the terminal
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
// function to rearrange vehicles based on their starting coordinates
void simulation::rearrangeVehicles()
{
    std::stable_sort(sim_vehicles.begin(),sim_vehicles.end(),compare);
}
void simulation::updateXcoordinates()
{
    // function to update X coordinates of all the vehicles to their maximum possible values
    for(int k=0;k<sim_vehicles.size();k++)    
        sim_vehicles.at(k).updateXcoordinate(sim_road.getSignal()-1,sim_road.getLightSignal());  
}
void simulation::runSimulation(std::vector<vehicles> &v,std::vector<int> &add_time,bool till_end,int start_time, GLFWwindow* window,int end_time)
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
        // Printing to terminal
        std::cout<<"Time: "<<cnt<<std::endl;
        printMap();

        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        vehicles v1;
        int sig_pos;
        float sig_col;
        // displaying the traffic signal
        sig_pos = sim_road.getSignal();
            if(!sim_road.getLightSignal())
                sig_col = 1.0;
            else
                sig_col=0.0;
        glColor3f(sig_col,0,0);
        glRecti(sig_pos-1, -10, sig_pos, 0);

        glEnable(GL_BLEND); //Enable blending.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
        glColor4f(220.0, 220.0, 220.0, 0.3);
        glRecti(0, 0, sim_road.getLength() , -1*sim_road.getWidth());
        glColor4f(255, 255, 255, 0.5);
        for(int stripe_x=0;stripe_x<sim_road.getLength();stripe_x+=4)
        {
            glRecti(stripe_x, -1*(sim_road.getWidth() /2) +1, stripe_x+2, (-1*sim_road.getWidth() /2));
        }
        
        glDisable(GL_BLEND);

        // Displaying different vehicles at different points in time
        for(int i=0;i<sim_vehicles.size();i++)
        {
    
            v1 = sim_vehicles.at(i);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            float dum_x = v1.getXcoordinateStart();
            float dum_y = -1*v1.getYcoordinateStart()-0.1;
            float dum_x_end = v1.getXcoordinateEnd();
            float dum_y_end = -1*v1.getYcoordinateEnd()-1+0.1;
            std::string dum_col = v1.getColour();
            float r=0.0,g=0.0,b = 0.0;
            if(dum_col == "RED")
                r=1.0;
            else
                r=0.0;
            if(dum_col == "BLUE")
                b=1.0;
            else
                b=0.0;
            if(dum_col == "GREEN")
                g=1.0;
            else
                g=0.0;
            std::cout<<"x_start,x_end,y_start,y_end, color are "<<dum_x<<", "<<dum_x_end<<", "<<dum_y<<", "<<dum_y_end<<", "<<dum_col<<"\n";
            glColor3f(r, g, b);
            glRectf(dum_x, dum_y, dum_x_end, dum_y_end);
               
        }
        //glRecti(GLint x1, GLint y1, GLint x2, GLint y2)
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


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
        rearrangeVehicles();
        updateXcoordinates(); 
        usleep(sec_1);
    }
}
std::vector<vehicles> simulation::getSimVehicles()
{
    return sim_vehicles;
}
// int main(int argc, char const *argv[])
// {
//     road r1(1,50,5,30,false);
//     std::vector<vehicles> v;
//     std::vector<int> t;
//     t.push_back(1);
//     t.push_back(2);
//     t.push_back(3);
//     simulation s(r1,v);
//     vehicles v2("Truck","",3,3,0,1,1,1);
//     vehicles v1("Car","",2,2,0,3,2,1);
//     vehicles v3("bike","",1,1,0,2,5,2);
//     v.push_back(v1);
//     v.push_back(v2);
//     v.push_back(v3);
//     s.runSimulation(v,t,false,0,40);
//     v3.setYcoordinate(3);
//     v.push_back(v3);
//     t.push_back(41);
//     s.setSignal(true);
//     s.runSimulation(v,t,true,42);
//     return 0;
// }



