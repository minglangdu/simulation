#pragma once // if the file is included multiple times, only one duplicate will exist.

#include <vector>
#include <iostream>
#include <string>
#include <map>

namespace map {
    class Object {
        public:
            std::string name;
            std::map<std::string, int> attr; // a value of 0 is default value.
            std::string use(std::string type); 
        // return value is output on using. 
        // type is player verb type (apply, zap, etc)
            Object(std::string nm, std::map<std::string, int> attributes);
    };
    class Map;
    struct Location {
        int x = -1, y = -1;
        std::vector<Object> objects;
        Map* chunk = nullptr; // chunk location is part of
        Location(std::vector<Object> o);
    };
    class Map {
        public:
            Map(std::vector<std::vector<Location*>> m); // normal init
            Map(int n, int m); // overloaded quick constructor
            std::vector<std::vector<Location*>> matrix;
            std::vector<std::vector<int>> passable;
    };
}