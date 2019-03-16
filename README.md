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

##Some salient points
 - The visualization is modeled to look like a real road. The road is grey with white stripes in the middle. Potholes aer maked by the red areas
 - The traffic signal, which is a square on top of the road. It turns red and green according to the traffic signal
 - The vehicles can overtake each other, provided that it is physically possible
 - During overtaking, vehicles blow horns, which is simulated using the system beep '\a'.    