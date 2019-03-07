#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "road.cpp"
#include "Vehicles.cpp"
#include "simulation.cpp"
using namespace std;
void vec_print(vector<int> &v);
int main() {

	//Define all default values
	int road_id=1, road_length=30, road_width=5, road_signal=15;
	float def_speed=1.0f, def_acc=1.0f;
	bool color_signal=false;
	int y=0;//y coordinate wher the vehicle is to be added
	simulation s1;
	//These are the vectors containing the condensed information of the config file
	vector<vehicles> vcls;	//vector of vehicles in order of their entry.
	vector<int> v_times;	//vector of the time instances when vehicles enter. Has same size as vcls
	vector<int> sig_times;	//vector of the time instances when signals change
	vector<bool>sig_colors;	//vector of the signal states. same size as sig_times
	vector<string> colors;	//vector of colors of vehicles. same size as vcls
	//vehicle specs
	string vtype="NONE";
	int v_count=0;
	int t=1;
	int c_l=0,c_w=0,b_l=0,b_w=0,bus_l=0,bus_w=0,t_l=0,t_w=0;
	float c_ms=def_speed, c_acc = def_acc, b_ms=def_speed, b_acc = def_acc, bus_ms=def_speed, bus_acc = def_acc, t_ms=def_speed, t_acc = def_acc;

	string line;
	string word;
	//printf("Opening file\n");
	ifstream config_file ("config.ini");
	if (config_file.is_open())
	{

		bool sim_start=false;
		while(getline(config_file,line))
		{
			
			//do this line-wise
			stringstream wstr(line);
			vector<string> words;
			while(wstr>>word)
			{
				//cout<<word<<endl;
				if(word[0]=='#')
					break;
				//cout<<word<<" ";
				words.push_back(word);
			}
			//cout<<endl;
			//Decide the assignment on the basis of words vector 
			if(words.size()<1)
				continue;
			if(!sim_start)
			{
				if(words.at(0)=="Road_Id")
					road_id = stoi(words.at(2));
				else if(words.at(0)== "Road_Length")
					road_length = stoi(words.at(2));
				else if(words.at(0)=="Road_Width")
					road_width = stoi(words.at(2));
				else if(words.at(0)=="Road_Signal")
					road_signal = stoi(words.at(2));
				else if(words.at(0)=="Default_MaxSpeed")
					def_speed = stof(words.at(2)); 
				else if(words.at(0)=="Default_Acceleration")
					 def_acc = stof(words.at(2)); 

				else if(words.at(0)=="Vehicle_Type")
				{
					vtype = words.at(2);
				}

				else if(words.at(0)=="Vehicle_Length")
				{
					if(vtype=="Car")
						c_l = stoi(words.at(2));
					if(vtype=="bike")
						b_l = stoi(words.at(2));
					if(vtype=="Bus")
						bus_l = stoi(words.at(2));
					if(vtype=="Truck")
						t_l = stoi(words.at(2));
				}

				else if(words.at(0)=="Vehicle_Width")
				{
					if(vtype=="Car")
						c_w = stoi(words.at(2));
					if(vtype=="bike")
						b_w = stoi(words.at(2));
					if(vtype=="Bus")
						bus_w = stoi(words.at(2));
					if(vtype=="Truck")
						t_w = stoi(words.at(2));
				}

				else if(words.at(0)=="Vehicle_MaxSpeed")
				{
					if(vtype=="Car")
						c_ms = stoi(words.at(2));
					if(vtype=="bike")
						b_ms = stoi(words.at(2));
					if(vtype=="Bus")
						bus_ms = stoi(words.at(2));
					if(vtype=="Truck")
						t_ms = stoi(words.at(2));
				}

				else if(words.at(0)=="Vehicle_Acceleration")
				{
					if(vtype=="Car")
						c_acc = stoi(words.at(2));
					if(vtype=="bike")
						b_acc = stoi(words.at(2));
					if(vtype=="Bus")
						bus_acc = stoi(words.at(2));
					if(vtype=="Truck")
						t_acc = stoi(words.at(2));
				}

				else if(words.at(0)=="START")
					{
						sim_start=true;
						road r1(road_id,road_length,road_width,road_signal,false);
						s1.setRoad(r1);
					}
			}
			else
			{
				if(words.at(0)=="Signal")
				{
					
					if(words.at(1)=="RED")
						{
							sig_colors.push_back(false);
							sig_times.push_back(t+v_count);
							s1.setSignal(false);
						}
					else if(words.at(1)=="GREEN")
						{
							sig_colors.push_back(true);
							sig_times.push_back(t+v_count);
							s1.setSignal(true);	
						}
					v_count=0;
				}
				if(words.at(0)=="Car")
				{
					if(y + c_w > road_width)
						y=0;
					vcls.push_back(vehicles("Car","",c_l,c_w,0,y,c_ms,c_acc));
					y+=c_w; 
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				else if(words.at(0)=="bike")
				{
					if(y + b_w > road_width)
						y=0;
					vcls.push_back(vehicles("bike","",b_l,b_w,0,y,b_ms,b_acc));
					y+=b_w; 
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				else if(words.at(0)=="Bus")
				{
					if(y + bus_w > road_width)
						y=0;
					vcls.push_back(vehicles("Bus","",bus_l,bus_w,0,y,bus_ms,bus_acc));
					y+=bus_w; 
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				else if(words.at(0)=="Truck")
				{
					if(y + t_w > road_width)
						y=0;
					vcls.push_back(vehicles("Truck","",t_l,t_w,0,y,t_ms,t_acc));
					y+=t_w; 
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				if(words.at(0)=="Pass")
				{
					s1.runSimulation(vcls,v_times,false,t-1,t+vcls.size()+stoi(words.at(1))-2);
					t += (v_count+stoi(words.at(1))-1);
					v_count=0;
				}
				if(words.at(0)=="END")
				{
					s1.runSimulation(vcls,v_times,true,t);
					break;
				}
			}
		}
		config_file.close();
	}
	else cout<<"Cannot open File! ";
	cout<<endl;
	return 0;
}

void vec_print(vector<int> &v)
{
	for(int i=0;i<v.size();i++)
		cout<<v.at(i)<<endl;
}

void vecs_print(vector<string> &v)
{
	for (int i = 0; i < v.size(); i++)
		cout<<v.at(i)<<endl;
}