# Indian Road Traffic Simulator
********************************************************
This is a road Traffic simulator built in c++ using opengl  
Version: 1.0  
By: Siddhant Mago, 2017CS50419  
    Jay Nitin Paranjape, 2017CS10355
********************************************************
## Description
In this assignment we simulated a road traffic intersection
in c++ using openGl. We did so only for uni-directional road 
where the traffic flows only in a single direction. We also added 
a traffic signal where the vehicles may or may not stop, depending on the colour of the signal. In the case of stopping we have assumed that deceleration can tend to infinity ie we have assumed instant stopping to prevent an accident. Furthermore, we have used newton laws of motion to govern the movement of different vehicles on the road.

## Configuration
We have used an `.ini` file similar to config.ini to run our simulation.

## Running the simulation
Ensure that you have glfw installed on your system and then run the `make` command on the terminal. An executable by the name of sim will be created, to run the simulation type `./sim` on the terminal 
