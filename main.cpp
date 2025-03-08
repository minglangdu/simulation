#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "map.h"
#include "ai.h"

using std::string;
using std::vector;
using std::cout;
using std::ifstream;
using std::get;

void LoadRaws() {
    ifstream order("raws/loadorder.txt");
    string file;
    while (std::getline(order, file)) {
        map::init_objs(file);
        map::init_biomes(file);
    }
}

int main() {
    LoadRaws();
    map::Object* wall = &(map::obj_types["WALL"]);
    cout << wall->use("hit") << "\n";
    auto t = wall->getattr("CONSTRUCTION");
    cout << get<0> (t) << " " << get<1> (t) << " " << get<2> (t) << "\n";
    auto u = wall->getattr("INVALID_TEST");
    cout << get<0> (u) << " " << get<1> (u) << " " << get<2> (u) << "\n";
    map::Creature* crea = new map::Creature("PIG", "Boar", {});
    auto v = crea->getattr("TERRAIN");
    cout << get<0> (v) << " " << get<1> (v) << " " << get<2> (v) << "\n";
}