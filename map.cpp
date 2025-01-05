#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "map.h"

using namespace std;

string map::Object::use(string type) {
    cout << name << " used. Type:" << type << "\n";
}

map::Object::Object(string nm, std::map<string, int> attributes) {
    name = nm;
    attr = attributes;
};

map::Location::Location(vector<map::Object> o) {
    objects = o;
}

map::Map::Map(vector<vector<map::Location>> m) {
    matrix = m;
    // passability: 
    // 5 is maximum passability
    // multiply passability with base speed of an npc.
    // 0 is impassible.
    vector<vector<int>> p (matrix.size(), vector<int> (matrix[0].size(), 5));
    for (int i = 0; i < matrix.size(); i ++) {
        for (int j = 0; j < matrix[0].size(); j ++) {
            int cur = 0;
            bool impass = false;
            for (Object o : matrix[i][j].objects) {
                cur += o.attr["difficulty"];
                if (o.attr["difficulty"] == -1) {
                    impass = true;
                    break;
                }
            }
            if (impass) p[i][j] = 0;
            else p[i][j] = max(1, 5 - cur);
        }
    }
    passable = p;
}