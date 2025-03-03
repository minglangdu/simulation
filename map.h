#pragma once // if the file is included multiple times, only one duplicate will exist.

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>

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
    std::map<std::string, std::map<std::string, std::string>> parse(std::string path, std::set<std::string> ptypes);
}