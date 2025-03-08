#pragma once // if the file is included multiple times, only one duplicate will exist.

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <tuple>

#include "ai.h"

namespace map {
    // Different types of objects
    class Object { // inanimate objects
        public:
            std::string name, id;
            std::tuple<std::string, double, bool> getattr(std::string key);
            std::string use(std::string type); 
        // return value is output on using. 
        // type is player verb type (apply, zap, etc)
            Object(std::string idd, std::string nm, std::map<std::string, std::string> attributes);
            Object(std::string idd);
            Object();
        protected: // so that Creature can use it
            std::map<std::string, std::string> attr; // a value of 0 is default value.
    };

    class Creature : public Object {
        public:
            Creature(std::string idd, std::string nm, std::map<std::string, std::string> attributes);
            std::string update(); // returns what the creature is doing
            ai::Decisionmaker mind;
    };

    // Groups of objects
    class Biome { // type of location
        public:
            // constructor function here
            Biome(std::string name);
            std::string name;
            std::map<std::string, std::string> attr;
        private:

    };
    class Location { // singular location
        public:
            // constructor function here
            Location(std::pair<int, int> c, std::tuple<int, int, int> xyz);
            Object terrain;
            std::vector<Object> parts;
            const int cx, cy; // chunk x, chunk y
            const int x, y, z;
            
        private:
            std::vector<Creature> creatures; // storage for creatures
    };
    class Chunk { // entire vertical subsection of map
        public:
            // constructor function here
            Chunk(std::pair<int, int> c, std::string biome);
            Biome biome;
            std::vector<std::vector<std::vector<Location>>> locs;
            const int cx, cy; // chunk x, chunk y
            
            bool loaded;
        private:
            std::vector<Creature> creatures; // storage for creatures
    };
    extern std::vector<std::vector<Chunk>> whole; // entire map
    // Parsing and Raws
    extern std::map<std::string, Object> obj_types; // extern prevents the variable from being defined, only declared
    std::map<std::string, Object> init_objs(std::string path);
    std::map<std::string, std::map<std::string, std::string>> parse(std::string path, std::set<std::string> ptypes);
}