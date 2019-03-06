#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "road.h"
#include "Vehicles.h"
using namespace std;

void vec_print(vector<int> &v);
void vecs_print(vector<string> &v);

int main() {

	int road_id=1, road_length=30, road_width=5, road_signal=15;
	float def_speed=1.0f, def_acc=1.0f;
	bool color_signal=false;
	vector<vehicles> vcls;
	vector<int> v_times;
	vector<int> sig_times;
	vector<bool>sig_colors;
	vector<string> colors;
	string vtype="NONE";
	int v_count=0;
	int t=0;
	int c_l=0,c_w=0,b_l=0,b_w=0,bus_l=0,bus_w=0,t_l=0,t_w=0;
	float c_ms=def_speed, c_acc = def_acc, b_ms=def_speed, b_acc = def_acc, bus_ms=def_speed, bus_acc = def_acc, t_ms=def_speed, t_acc = def_acc;

	string line;
	string word;
	printf("Opening file\n");
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
				if(word[0]=='#')
					break;

				words.push_back(word);
			}
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
					sim_start=true;
			}
			else
			{
				if(words.at(0)=="Signal")
				{
					
					if(words.at(1)=="RED")
						{
							sig_colors.push_back(false);
							sig_times.push_back(t+v_count);
						}
					else if(words.at(1)=="GREEN")
						{
							sig_colors.push_back(true);
							sig_times.push_back(t+v_count);	
						}
					v_count=0;
				}

				if(words.at(0)=="Car")
				{
					vcls.push_back(vehicles("Car",c_l,c_w,0,0,c_ms,c_acc));
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				else if(words.at(0)=="bike")
				{
					vcls.push_back(vehicles("bike",b_l,b_w,0,0,b_ms,b_acc));
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				else if(words.at(0)=="Bus")
				{
					vcls.push_back(vehicles("Bus",bus_l,bus_w,0,0,bus_ms,bus_acc));
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}
				else if(words.at(0)=="Truck")
				{
					vcls.push_back(vehicles("Truck",t_l,t_w,0,0,t_ms,t_acc));
					v_times.push_back(t + v_count);
					colors.push_back(words.at(1));
					v_count++;
				}

				if(words.at(0)=="Pass")
				{
					t+=stoi(words.at(1));
					v_count=0;
				}
			}
		}

		config_file.close();
	}
	else cout<<"Cannot open File! ";
	cout<<"Hello"<<endl;
	vec_print(v_times);
	vec_print(sig_times);
	vecs_print(colors);

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