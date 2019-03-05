OBJS = INIReaderExample.o ini.o INIReader.o
SOURCE = INIReaderExample.cpp ini.c INIReader.cpp
OUT = main
CXXFLAGS =-Wall -g -O2
all: $(OUT)

$(OUT): $(OBJS)
	g++ $(OBJS) -o $(OUT) $(CXXFLAGS)

INIReaderExample.o: INIReaderExample.cpp	INIReader.h
	g++ -c INIReaderExample.cpp -o $@

ini.o: ini.c ini.h
	gcc -c ini.c -o $@

INIReader.o: INIReader.cpp INIReader.h ini.h
	g++ -c INIReader.cpp -o $@

clean:
	rm *.o
	rm main