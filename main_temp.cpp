#include <iostream>
#include <unistd.h>
#include "Vehicles.h"
#include "road.h"
// defining sec_1 as 10^6 microseconds
const long sec_1 = 1000000;
int main(int argc, char const *argv[])
{
    road r1(1,15,4,8,false);
    vehicles v("Car");
    int cnt = 0;
    while(v.getXcoordinateEnd()<r1.getLength())
    {
        cnt++;
        std::cout<<"Time: "<<cnt<<std::endl;
        for(int i=0;i<r1.getWidth();i++)
        {
            for(int j=0;j<r1.getLength();j++)
            {
                if(j<=v.getXcoordinateStart() && j>=v.getXcoordinateEnd() && i>=v.getYcoordinateStart() && i<=v.getYcoordinateEnd())
                    std::cout<<v.getRepresentation();
                else
                    std::cout<<" ";
                if (j==r1.getSignal()-1 && r1.getLightSignal()==false)
                    std::cout<<"|";    
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        if(cnt == 20)
            r1.setLightSignal(true);
        v.setXcoordinate(r1.getSignal()-1,r1.getLightSignal());
        usleep(sec_1);
    }    
    return 0;
}
