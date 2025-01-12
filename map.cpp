#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "map.h"

using std::string;
using std::cout;
using std::vector;
using std::ifstream;

std::map<string, map::Object> map::obj_types = {};
std::map<string, map::Object> map::init_objs(string path) {
    ifstream objraw(path);
    string line;
    string l = "", r = "";
    Object tem("tem");
    bool indef = false; // stores if we are reading the body of an object or not
    bool ignore = false;
    bool inright = false;
    while (getline(objraw, line)) {
        for (int i = 0; i < line.size(); i ++) {
            if (line[i] == '[') {
                cout << "left bracket\n";
                l = "";
                inright = false;
            } 
            else if (line[i] == ':') {
                cout << "(gd) colon: ";
                cout << l << "\n";
                inright = true;
                if (!indef) {
                    if (l != "OBJECT") ignore = true;
                }
                r = "";
            }
            else if (line[i] == ']') {
                cout << "right bracket: ";
                cout << l << " " << r << "\n";
                if (indef) { // means just finished reading attribute
                    cout << "INDEF\n";
                    if (l == "NAME") { // hardcode for now
                        tem.name = r;
                    }
                    obj_types[tem.id].attr[l] = r;
                }
                else { // means you finished reading object declaration
                    indef = true; 
                    cout << "NOW INDEF\n";
                    tem.id = r;
                    obj_types[tem.id] = tem;
                }
                if (l == "ENDDEF") {
                    cout << "NOT INDEF\n";
                    ignore = false;
                    indef = false;
                }
                if (ignore) continue;
            }
            else if (!inright) {
                l += line[i];
            } else if (inright) {
                r += line[i];
            }
        }
    }
    return obj_types;
}

string map::Object::use(std::string type) {
    return name + " used. Type:" + type + "\n";
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

map::Location::Location(vector<map::Object> o) {
    objects = o;
}

int map::Map::GetPass(map::Location* loc) {
    /*
    passability: 
    5 is maximum passability
    multiply passability with base speed of an npc.
    0 is impassible.
    */
    int cur = 0;
    bool impass = false;
    for (Object o : loc->objects) {
        int current;
        try {
            current = std::stoi(o.attr["DIFFICULTY"]);
        }
        catch (...) {
            current = 0;
        }
        cur += current;
        if (current == -1) {
            impass = true;
            break;
        }
    }
    if (impass) return 0;
    else return std::max(1, 5 - cur);
}

map::Map::Map(vector<vector<map::Location*>> m) {
    for (int i = 0; i < m.size(); i ++) {
        for (int j = 0; j < m[0].size(); j ++) {
            m[i][j]->x = j;
            m[i][j]->y = i;
            m[i][j]->chunk = this;
        }
    }
    matrix = m;
    vector<vector<int>> p (matrix.size(), vector<int> (matrix[0].size(), 5));
    for (int i = 0; i < matrix.size(); i ++) {
        for (int j = 0; j < matrix[0].size(); j ++) {
            p[i][j] = GetPass(matrix[i][j]);
        }
    }
    passable = p;
}

vector<vector<map::Location*>> generate_empty(int n, int m) {
    map::Location* empty = new map::Location(vector<map::Object> ());
    vector<vector<map::Location*>> v (n, vector<map::Location*> (m, empty));
    return v;
}

map::Map::Map(int n, int m) : Map(generate_empty(n, m)) {
    // quick initialization
    // uses an initializer list
}

vector<vector<map::Location*>> map::Map::ChangeCells(int x1, int y1, int x2, int y2, 
vector<vector<map::Location*>> l) {
    for (int i = y1; i <= y2; i ++) {
        for (int j = x1; j <= x2; j ++) {
            matrix[i][j] = l[i - y1][j - x1];
            passable[i][j] = GetPass(matrix[i][j]);
        }
    }
    return matrix;
}

vector<vector<map::Location*>> map::Map::ChangeCells(int x1, int y1, int x2, int y2, 
map::Location* l) {
    return map::Map::ChangeCells(x1, y1, x2, y2, vector<vector<map::Location*>> (x2 - x1 + 1, 
vector<map::Location*> (y2 - y1 + 1, l)));
}

vector<vector<map::Location*>> map::Map::ChangeCell(int x, int y, map::Location* l) {
    vector<vector<map::Location*>> mat (1, vector<map::Location*> (1, l));
    return map::Map::ChangeCells(x, y, x, y, mat);
}

vector<vector<map::Location*>> map::Map::GetMatrix() {
    return matrix;
}
vector<vector<int>> map::Map::GetPassMat() {
    return passable;
}