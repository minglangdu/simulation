#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <set>
#include <tuple>
#include <cmath>

#include "map.h"

using std::string;
using std::cout;
using std::vector;
using std::ifstream;
using std::stoi;
using std::string;

const bool DEBUG = false;

/*
Parsing
*/

std::map<string, map::Object> map::obj_types = {};

std::map<string, std::map<string, string>> map::parse(string path, std::set<string> ptypes) {
    ifstream raw(path);
    string line;
    string l = "", r = "";
    bool indef = false; // store if we are in the definition of something.
    bool ignore = false; 
    bool inright = false;
    std::map<string, std::map<string, string>> res; 
    string id = "";
    while (getline(raw, line)) {
        for (int i = 0; i < line.size(); i ++) {
            if (line[i] == '[') {
                if (DEBUG) cout << "left bracket\n";
                l = "";
                inright = false;
            } 
            else if (line[i] == ':') {
                if (DEBUG) {
                    cout << "(gd) colon: ";
                    cout << l << "\n";
                }
                inright = true;
                if (!indef) { // means type has just been defined
                    if (!ptypes.count(l)) { // checks if it is not in parsing types
                        ignore = true;
                        if (DEBUG) cout << "IGNORING\n";
                    }
                }
                r = "";
            }
            else if (line[i] == ']') {
                if (DEBUG) {
                    cout << "right bracket: ";
                    cout << l << " " << r << "\n";
                }
                if (indef) { // means just finished reading attribute
                    if (l == "ENDDEF") {
                        if (DEBUG) cout << "NOT INDEF\n";
                        ignore = false;
                        indef = false;
                    }
                    res[id][l] = r;
                }
                else { // means you finished reading object declaration
                    if (ignore) continue;
                    indef = true; 
                    if (DEBUG) cout << "NOW INDEF\n";
                    id = r;
                    res[id] = {};
                    if (DEBUG) cout << "ID " << id << "\n";
                }
            }
            else if (!inright) {
                l += line[i];
            } else if (inright) {
                r += line[i];
            }
        }
    }
    return res;
}

std::map<string, map::Object> map::init_objs(string path) {
    std::map<string, std::map<string, string>> parsed = parse(path, std::set<string> {"OBJECT"});
    for (auto obj : parsed) {
        string name;
        try {
            name = obj.second["NAME"];
            obj.second.erase("NAME");
        } catch (...) {
            name = "Unnamed Object";
        }
        obj_types[obj.first] = Object(obj.first, name, obj.second);
        if (DEBUG) {
            cout << "ID " << obj.first << "\n";
            cout << "NAME " << obj.second["NAME"] << "\n";
            cout << "----\n";
        }
    }
    return obj_types;
}

/*
Object
*/

string map::Object::use(std::string type) {
    return name + " used. Type:" + type;
}

map::Object::Object(string idd, string nm, std::map<string, string> attributes) {
    id = idd;
    name = nm;
    attr = attributes;
};

map::Object::Object(string idd) : map::Object::Object(idd, "Empty Object", {}) {
    // initializer list used here
}

map::Object::Object() : map::Object::Object("More Empty Object lol") {
    // more initializer list
}

std::tuple<string, double, bool> map::Object::getattr(string key) {
    string s = attr[key];
    double d;
    try {
        double d = std::stod(s);
        if (d == RLIM_INFINITY || isnan(d)) {
            d = 0;
        }
    } catch (...) {
        d = 0;
    }
    bool b = false;
    if (s == "YES") b = true;
    return {s, d, b};
}

/*
Creature
*/



/*
Biome
*/



/*
Location
*/



/*
Chunk
*/