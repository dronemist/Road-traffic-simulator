// Example that shows simple usage of the INIReader class

#include <iostream>

// Read an INI file into easy-to-access name/value pairs.

// inih and INIReader are released under the New BSD license (see LICENSE.txt).
// Go to the project home page for more info:
//
// https://github.com/benhoyt/inih


#include "INIReader.h"

int main()
{
    INIReader reader("config.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'test.ini'\n";
        return 1;
    }
    int def_speed = reader.GetInteger("DEFAULTS", "Default_MaxSpeed", 1);
    int def_acc = reader.GetInteger("DEFAULTS","Default_Acceleration",1);
    std::cout << "Config loaded from 'test.ini': road_ID="
              << reader.GetInteger("ROAD_PARAMS","Road_Id", 1) << ", CAR SPEED="
              << reader.GetInteger("CAR", "Vehicle_MaxSpeed", def_speed)<<'\n'; //<< ", email="
              // << reader.Get("user", "email", "UNKNOWN") << ", pi="
              // << reader.GetReal("user", "pi", -1) << ", active="
              // << reader.GetBoolean("user", "active", true) << "\n";
    return 0;
}
