#include <iostream>

#include "map.h"
#include "ai.h"

using std::string;
using std::vector;
using std::cout;

int main() {
    map::Object wall = map::Object("Wall", {{"difficulty", -1}});
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
}