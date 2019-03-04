#include <iostream>
#include <unistd.h>
#include <vector>
#include "Vehicles.cpp"
#include "road.cpp"
// defining sec_1 as 10^6 microseconds
const long sec_1 = 1000000;
int main(int argc, char const *argv[])
{
    road r1(1,30,4,15,false);
    vehicles v[3];
    vehicles v2("Truck",3,3,-1,1,1,1);
    vehicles v1("Car",2,2,-1,0,2,1);
    vehicles v3("bike",1,1,-1,0,3,3);
    v[0] = v1; v[1] = v2; v[2] = v3;
    std::vector<std::vector<int>> map(r1.getWidth(),std::vector<int>(r1.getLength()));    
    int cnt = 0;
    while(v[2].getXcoordinateEnd()<r1.getLength())
    {
        for(int k=0;k<3;k++)
        {
            for(int i=0;i<r1.getWidth();i++)
            {
                for(int j=0;j<r1.getLength();j++)
                {
                    if(map.at(i).at(j) > k)
                            map.at(i).at(j) = 0; 
                    if (j==r1.getSignal()-1 && r1.getLightSignal()==false)
                        map.at(i).at(j) = -1;
                    if (j==r1.getSignal()-1 && r1.getLightSignal()==true && map.at(i).at(j)==-1)
                    {
                        map.at(i).at(j) = 0;
                    }                     
                    if( k>0 
                    && v[k].getXcoordinateStart() >= v[k-1].getXcoordinateEnd() 
                    && v[k].getYcoordinateStart() <= v[k-1].getYcoordinateEnd()
                    && v[k].getYcoordinateEnd() >= v[k-1].getYcoordinateEnd())
                    {
                        v[k].setXcoordinate(std::max(v[k-1].getXcoordinateEnd()-1,-1));
                        v[k].setCurrSpeed(std::min(v[k-1].getCurrSpeed(),v[k].getCurrSpeed()));
                    }
                    if(j<=v[k].getXcoordinateStart() && j>=v[k].getXcoordinateEnd() && i>=v[k].getYcoordinateStart() && i<=v[k].getYcoordinateEnd())
                        map.at(i).at(j) = k+1;
                         
                }
            }
        }  
        cnt++;
        std::cout<<"Time: "<<cnt-1<<std::endl;
        for(int i=0;i<r1.getWidth();i++)
        {
            for(int j=0;j<r1.getLength();j++)
            {
                int temp = map.at(i).at(j); 
                if(temp>0)
                    std::cout<<v[temp-1].getRepresentation();
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
        if(cnt == 20)
            r1.setLightSignal(true);
        for(int k =0;k<std::min(3,cnt);k++)    
            v[k].updateXcoordinate(r1.getSignal()-1,r1.getLightSignal());   
        usleep(sec_1);
    }    
    return 0;
}
