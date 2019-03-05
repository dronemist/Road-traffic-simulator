OBJS = main_temp.o road.o Vehicles.o
SOURCE = main_temp.cpp road.cpp Vehicles.cpp
OUT = sim
CXXFLAGS =-Wall -g
CXX = g++

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(CXXFLAGS)

main_temp.o: main_temp.cpp Vehicles.h road.h
	$(CXX) -c main_temp.cpp -o $@

road.o: road.cpp road.h
	$(CXX) -c road.cpp -o $@

Vehicles.o: Vehicles.cpp Vehicles.h
	$(CXX) -c Vehicles.cpp -o $@

clean:
	rm *.o
	rm $(OUT)