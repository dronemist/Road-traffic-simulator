OBJS = parse_ini.o simulation.o road.o Vehicles.o
SOURCE =parse_ini.cpp simulation.cpp road.cpp Vehicles.cpp
OUT = sim
CXXFLAGS =-Wall -g -lglut -lGLU -lGL
CXX = g++

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(CXXFLAGS)

parse_ini.o: parse_ini.cpp simulation.h Vehicles.h road.h

simulation.o: simulation.cpp simulation.h Vehicles.h road.h
	$(CXX) -c simulation.cpp -o $@

road.o: road.cpp road.h
	$(CXX) -c road.cpp -o $@

Vehicles.o: Vehicles.cpp Vehicles.h
	$(CXX) -c Vehicles.cpp -o $@

clean:
	rm *.o
	rm $(OUT)