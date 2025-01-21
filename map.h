#pragma once // if the file is included multiple times, only one duplicate will exist.

#include <vector>
#include <iostream>
#include <string>
#include <map>

namespace map {
    class Object {
        public:
            std::string name, id;
            std::map<std::string, std::string> attr; // a value of 0 is default value.
            std::string use(std::string type); 
        // return value is output on using. 
        // type is player verb type (apply, zap, etc)
            Object(std::string idd, std::string nm, std::map<std::string, std::string> attributes);
            Object(std::string idd);
            Object();
    };
    extern std::map<std::string, Object> obj_types; // extern prevents the variable from being defined, only declared
    std::map<std::string, Object> init_objs(std::string path);
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
            Map(int m, int n); // overloaded quick constructor

            int GetPass(Location* loc);

            std::vector<std::vector<Location*>> ChangeCells(int x1, int y1, 
            int x2, int y2, std::vector<std::vector<Location*>> l); // range from [x1, x2], [y1, y2] inclusive
            std::vector<std::vector<Location*>> ChangeCells(int x1, int y1, 
            int x2, int y2, Location* l);

            // changes that to the matrix specified
            std::vector<std::vector<Location*>> GetMatrix();
            std::vector<std::vector<int>> GetPassMat();

            std::vector<std::vector<Location*>> ChangeCell(int x, int y, Location* l); // same but for one cell
        
            std::vector<std::vector<std::string>> GetRep();
        private:
            std::vector<std::vector<Location*>> matrix;
            std::vector<std::vector<int>> passable;
    };
}