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

std::tuple<std::string, double, bool> geta(std::string key, std::map<std::string, std::string> attr) {
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
Parsing
*/

std::map<string, map::Object> map::obj_types = {};
std::map<string, map::Biome> map::biomes = {};

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

std::map<string, map::Biome> map::init_biomes(string path) {
    std::map<string, std::map<string, string>> parsed = parse(path, std::set<string> {"BIOME"});

    biomes = {};
    return biomes;
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
    return geta(key, attr);
}

/*
Creature
*/

map::Creature::Creature(string idd, string name, std::map<string, string> attributes)
 : map::Object::Object(idd, name, attributes) {
    mind = ai::Decisionmaker();
 }

string map::Creature::update() {
    // placeholder - find and enact actions here
    return "placeholder";
}

/*
Biome
*/

map::Biome::Biome(string nm, std::map<string, string> atr) {
    name = nm;
    attr = atr;
}

map::Biome::Biome(string nm) {
    biomes[nm] = *this;
}

map::Biome::Biome() {}

std::tuple<std::string, double, bool> map::Biome::getattr(std::string key) {
    return geta(key, attr);
}

/*
Location
*/

map::Location::Location(std::pair<int, int> c, std::tuple<int, int, int> xyz, Object terr) {
    cx = c.first; cy = c.second;
    x = std::get<0> (xyz); y = std::get<1> (xyz); z = std::get<2> (xyz);
    if (!std::get<2> (terr.getattr("TERRAIN"))) {
        throw std::invalid_argument("Terrain tile not terrain");
    }
    else {
        terrain = terr;
    }
}

/*
Chunk
*/

std::vector<std::vector<map::Chunk>> map::whole = {};

vector<vector<map::Chunk>> map::init_whole(int cxs, int cys, int csx, int csy, int csz) {
    for (int chy = 0; chy < cys; chy ++) {
        vector<map::Chunk> cur = {};
        for (int chx = 0; chx < cxs; chx ++) {
            string selbiome = "DESERT";
            cur.push_back(Chunk({chx, chy}, selbiome, csx, csy, csz));
        }
        whole.push_back(cur);
    }
    return whole;
}

vector<vector<vector<map::Location>>> genflat(string tile1, string tile2, int val1, int val2, int csx, int csy, int csz) {
    // tile 1: surface tile
    // tile 2: all tiles below surface.
    // Flat world with surface at z level val1 and end at z level csz - val2. 
    return {};
}

map::Chunk::Chunk(std::pair<int, int> c, string bi, int csx, int csy, int csz) {
    if (!biomes.count(bi)) {
        throw std::invalid_argument("Biome name not found.");
    }
    biome = biomes[bi];
    string type = std::get<0> (biome.getattr("GENERATION"));
    string tile1 = std::get<0> (biome.getattr("TILE1"));
    string tile2 = std::get<0> (biome.getattr("TILE2"));
    int val1 = std::get<1> (biome.getattr("VAL1"));
    int val2 = std::get<1> (biome.getattr("VAL1"));
    if (type == "FLAT") {
        locs = genflat(tile1, tile2, val1, val2, csx, csy, csz);
    } else {
        throw std::invalid_argument("Generation function not found.");
    }
    cx = c.first; cy = c.second;
}