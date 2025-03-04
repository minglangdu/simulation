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
        // put other init functions here: init_objs only scans for objects
    }
}

int main() {
    LoadRaws();
    map::Object* wall = &(map::obj_types["WALL"]);
    cout << wall->use("hit") << "\n";
    auto t = wall->getattr("CONSTRUCTION");
    cout << get<0> (t) << " " << get<1> (t) << " " << get<2> (t) << "\n";
}