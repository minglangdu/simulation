#pragma once // if the file is included multiple times, only one duplicate will exist.

#include <vector>
#include <iostream>
#include <string>
#include <map>

namespace map {
    class Object {
        public:
            std::string name;
            std::map<string, int> attr; // a value of 0 is default value.
            std::string use(std::string type); 
        // return value is output on using. 
        // type is player verb type (apply, zap, etc)
            Object(std::string nm, std::map<string, int> attributes);
    };

    struct Location {
        std::vector<Object> objects;
        Location(std::vector<Object>);
    };
    class Map {
        public:
            Map(std::vector<std::vector<Location>>);
            std::vector<std::vector<Location>> matrix;
            std::vector<std::vector<int>> passable;
    };
}