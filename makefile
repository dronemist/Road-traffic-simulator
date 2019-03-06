OBJS = simulation.o road.o Vehicles.o
SOURCE = simulation.cpp road.cpp Vehicles.cpp
OUT = sim
CXXFLAGS =-Wall -g
CXX = g++

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(CXXFLAGS)

simulation.o: simulation.cpp Vehicles.h road.h
	$(CXX) -c simulation.cpp -o $@

road.o: road.cpp road.h
	$(CXX) -c road.cpp -o $@

Vehicles.o: Vehicles.cpp Vehicles.h
	$(CXX) -c Vehicles.cpp -o $@

clean:
	rm *.o
	rm $(OUT)