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

const int CHUNKS_X = 5;
const int CHUNKS_Y = 5;
const int EDGE_SIZE = 25;
const int HEIGHT = 50;

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
    map::init_whole(CHUNKS_X, CHUNKS_Y, EDGE_SIZE, EDGE_SIZE, HEIGHT);
    
}