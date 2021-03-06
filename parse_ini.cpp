#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "road.h"
#include "Vehicles.h"
#include "simulation.h"
using namespace std;
void vec_print(vector<int> &v);

//void display(simulation);
// void reshape(int, int);
//void timer(int);

// void init()
// {
//     glClearColor(0.0,0.0,0.0,1.0);
// }

int main(int argc, char const *argv[]) {



	GLFWwindow* window; 
	
	/* Initialize the library */
    if (!glfwInit())
        {cout<<"Could not initialize library ";return -1;}

    /* Create a windowed mode window and its OpenGL context */
    

	// glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	// glutInitWindowPosition(200, 100);
	// glutInitWindowSize(500,500);

	// // glutCreateWindow("Indian Road");

	// // glutDisplayFunc(display);
	//  glutReshapeFunc(reshape);
    

	// // glutTimerFunc(0, timer,0);
	// init();

	// glutMainLoop();

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
	int c_l=0,c_w=0,b_l=0,b_w=0,bus_l=0,bus_w=0,t_l=0,t_w=0,a_l=0,a_w=0;
	float c_ms=def_speed, c_acc = def_acc,a_ms=def_speed,a_acc=def_acc, b_ms=def_speed, b_acc = def_acc, bus_ms=def_speed, bus_acc = def_acc, t_ms=def_speed, t_acc = def_acc;

	string line;
	string word;
	ifstream config_file (argv[1]);
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
				words.push_back(word);
			}
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
					{
						def_speed = stof(words.at(2)); 

						c_ms=def_speed; a_ms = def_speed;b_ms=def_speed; bus_ms=def_speed; t_ms=def_speed;
					}
				else if(words.at(0)=="Default_Acceleration")
					 {
					 	def_acc = stof(words.at(2)); 

						c_acc = def_acc;a_acc=def_acc; b_acc = def_acc; bus_acc = def_acc; t_acc = def_acc;
					 }

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
					if(vtype == "AutoRickshaw")
						a_l = stoi(words.at(2));
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
					if(vtype=="AutoRickshaw")
						a_w = stoi(words.at(2));
				}

				else if(words.at(0)=="Vehicle_MaxSpeed")
				{
					if(vtype=="Car")
						c_ms = stof(words.at(2));
						//cout<<"c_ms has been reset to "<<c_ms<<"and the stof was"<<words.at(2)<<endl;
					if(vtype=="bike")
						b_ms = stof(words.at(2));
					if(vtype=="Bus")
						bus_ms = stof(words.at(2));
					if(vtype=="Truck")
						t_ms = stof(words.at(2));
					if(vtype=="AutoRickshaw")
						a_ms = stof(words.at(2));
				}

				else if(words.at(0)=="Vehicle_Acceleration")
				{
					if(vtype=="Car")
						c_acc = stof(words.at(2));
					if(vtype=="bike")
						b_acc = stof(words.at(2));
					if(vtype=="Bus")
						bus_acc = stof(words.at(2));
					if(vtype=="Truck")
						t_acc = stof(words.at(2));
					if(vtype=="AutoRickshaw")
						a_acc = stof(words.at(2));
				}

				else if(words.at(0)=="START")
					{

						window = glfwCreateWindow((road_length)*21, road_width*40, "Indian Road", NULL, NULL);
    					if (!window)
    					{
        					{cout<<"Could not make window ";glfwTerminate();}
        					return -1;
    					}

    					glClearDepth(1);
						glEnable(GL_DEPTH_TEST);

					    /* Make the window's context current */
					    glfwMakeContextCurrent(window);

						sim_start=true;
						road r1(road_id,road_length,road_width,road_signal,false);
						s1.setRoad(r1);

						glViewport(0, 0, (float(road_length+2)/32)*640 + 4, (float(road_width+1)/10)*320 +4);
    					glMatrixMode(GL_PROJECTION);
    					glLoadIdentity();
    					gluOrtho2D(0,road_length+2,(-1*road_width-1) - (road_width/2) - 1,(road_width+1)/2);
    					glMatrixMode(GL_MODELVIEW);
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
				}
				if(words.at(0)=="Car")
				{
					if(y + c_w > road_width)
						y=0;
					//cout<<c_l<<" "<<c_w<<" "<<c_ms<<" "<<c_acc<<endl;
					vcls.push_back(vehicles("Car",words.at(1),c_l,c_w,0,y,c_ms,c_acc));
					v_times.push_back(t);
					s1.runSimulation(vcls,v_times,false,t,window,t);
					t++;
					y+=c_w;
				}
				else if(words.at(0)=="bike")
				{
					if(y + b_w > road_width)
						y=0;
					vcls.push_back(vehicles("bike",words.at(1),b_l,b_w,0,y,b_ms,b_acc));
					v_times.push_back(t);
					s1.runSimulation(vcls,v_times,false,t,window,t);
					t++;
					y+=b_w; 
				}
				else if(words.at(0)=="Bus")
				{
					if(y + bus_w > road_width)
						y=0;
					vcls.push_back(vehicles("Bus",words.at(1),bus_l,bus_w,0,y,bus_ms,bus_acc));
					v_times.push_back(t);
					s1.runSimulation(vcls,v_times,false,t,window,t);
					t++;
					y+=bus_w; 
				}
				else if(words.at(0)=="Truck")
				{
					if(y + t_w > road_width)
						y=0;
					vcls.push_back(vehicles("Truck",words.at(1),t_l,t_w,0,y,t_ms,t_acc));
					v_times.push_back(t);
					s1.runSimulation(vcls,v_times,false,t,window,t);
					t++;
					y+=t_w; 
				}
				// code to add autorickshaw to simulation
				else if(words.at(0)=="AutoRickshaw")
				{
					if(y + a_w > road_width)
						y=0;
					vcls.push_back(vehicles("AutoRickshaw",words.at(1),a_l,a_w,0,y,a_ms,a_acc));
					v_times.push_back(t);
					s1.runSimulation(vcls,v_times,false,t,window,t);
					t++;
					y+=a_w; 
				}
				if(words.at(0)=="Pass")
				{
					s1.runSimulation(vcls,v_times,false,t,window,t+stoi(words.at(1))-1);
					t += stoi(words.at(1));
				}
				if(words.at(0)=="END")
				{
					s1.runSimulation(vcls,v_times,true,t,window);
					cout<<"The number of vehicles on the road are:"<<s1.getNumberOfVehicles();
					break;
				}
			}
		}
		config_file.close();
	}
	else cout<<"Cannot open File! ";
	cout<<endl;

	glfwTerminate();
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
//HERE I HAVE DEFINED A VARIABLE WHICH REPRESENTS THE X COORDINATE
//float dum_x = -10.0;
// void display(simulation s)
// {
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glLoadIdentity();
// 	// s.getSimVehicles(); this will give the vehicle vector
// 	//HERE I HAVE DEFINED A RECTANGLE WITH THE FIRST 2 COORDINATES REPRESENTING A VERTEX AND THE LAST 2, THE OPP. VERTEX
// 	//COULD YOU DO THE SAME FOR SIM_VEHICLES? I have defined coordinates for sim_vehicles in the same way 
// 	glRectd(dum_x, 1.0, dum_x+2.0, -1.0);
// 	//YOU CAN GIVE COLOR ACCD TO THE INI FILE AND THE POSITION ACCORDING TO THE SIMULATION. FOR THAT WE NEED THOSE
// 	// DATA POINTS GLOBALLY. SO EXTRACT THEM AS VECTORS AND MAKE THE NECESSARY RECTANGLES 

// 	glEnd();

// 	glutSwapBuffers();
// }



// void timer(int)
// {
// 	glutPostRedisplay();
// 	glutTimerFunc(1000/60, timer,0);
// 	dum_x+=0.15;
// 	//HERE YOU CAN COMMENT dum_x INCREMENT
// }
