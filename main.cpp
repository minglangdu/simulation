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
    cout << "-----\n";
    for (auto a : map::obj_types) {
        cout << a.first << " " << a.second.attr["DIFFICULTY"] << "|\n";
    }
    cout << "-----\n";
    map::Object wall = map::obj_types["WALL"];
    map::Location* loc = new map::Location(vector<map::Object> (1, wall));
    map::Map* mp = new map::Map(5, 5);
    mp->ChangeCells(1, 1, 3, 2, loc);
    vector<vector<int>> pass = mp->GetPassMat();
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            cout << pass[i][j] << " ";
        }
        cout << "\n";
    }
    cout << wall.attr["DESCRIPTION"] << "\n";
}