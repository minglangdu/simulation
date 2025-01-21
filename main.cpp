#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "map.h"
#include "ai.h"

using std::string;
using std::vector;
using std::cout;
using std::ifstream;

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
    map::Location* walloc = new map::Location(vector<map::Object> (1, map::obj_types["WALL"]));
    walloc->objects.push_back(map::obj_types["FLOOR"]);
    
    map::Location* sandloc = new map::Location(vector<map::Object> (1, map::obj_types["SAND_FLOOR"]));
    map::Map* mp = new map::Map(5, 5);
    
    cout << mp->GetMatrix()[0][0]->objects.size() << " " << mp->GetMatrix()[0][0]->x << " " << mp->GetMatrix()[0][0]->y << "\n";
    cout << "====\n";

    vector<vector<string>> pass = mp->GetRep();
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            cout << pass[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "----\n";
    mp->ChangeCells(0, 0, 4, 4, sandloc);
    mp->ChangeCells(1, 1, 3, 2, walloc);
    cout << "====\n";
    pass = mp->GetRep();
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            cout << pass[i][j] << " ";
        }
        cout << "\n";
    }
}