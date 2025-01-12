#include <iostream>

#include "map.h"
#include "ai.h"

using std::string;
using std::vector;
using std::cout;

int main() {
    map::Map* mp = new map::Map(5, 5);
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            cout << mp->passable[i][j] << " ";
        }
        cout << "\n";
    }
}