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

const bool DEBUG = false;

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
                if (!indef) {
                    if (l != "OBJECT") {
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
                    // cout << "INDEF\n";
                    if (l == "NAME") { // hardcode for now
                        tem.name = r;
                    }
                    obj_types[tem.id].attr[l] = r;
                }
                else { // means you finished reading object declaration
                    if (ignore) continue;
                    indef = true; 
                    if (DEBUG) cout << "NOW INDEF\n";
                    tem.id = r;
                    obj_types[tem.id] = tem;
                }
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
    cout << "--init1--\n";
    cout << m[1][1]->objects.size() << "\n";
    for (int i = 1; i < m.size(); i ++) {
        for (int j = 1; j < m.size(); j ++) {
            cout << m[i][j]->objects.size() << "\n";
        }
    }
    for (int i = 0; i < m.size(); i ++) {
        for (int j = 0; j < m[0].size(); j ++) {
            cout << "-\n" << i << " " << j << " " << m[i][j]->objects.size() << "\n";
            map::Location tem = Location(m[i][j]->objects);
            tem.x = j;
            tem.y = i;
            tem.chunk = this;
            m[i][j] = &tem;
            cout << tem.x << " " << tem.y << " " << tem.objects.size() << "\n";
            cout << m[i][j]->x << " " << m[i][j]->y << " " << m[i][j]->objects.size() << "\n";
            cout << m[0][0]->x << " " << m[0][0]->y << " " << m[0][0]->objects.size() << "\n";
        }
    }
    matrix = m;
    cout << "set matrix\n";
    vector<vector<int>> p (matrix.size(), vector<int> (matrix[0].size(), 5));
    for (int i = 0; i < matrix.size(); i ++) {
        for (int j = 0; j < matrix[0].size(); j ++) {
            p[i][j] = GetPass(matrix[i][j]);
        }
    }
    passable = p;
}

vector<vector<map::Location*>> generate_empty(int n, int m) {
    cout << "--generate empty--\n";
    vector<vector<map::Location*>> v (n, vector<map::Location*> (m));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            map::Location next = map::Location(vector<map::Object> (0));
            next.x = j;
            next.y = i;
            cout << "-\n";
            cout << next.x << " " << next.y << " " << next.objects.size() << "\n";
            v[i][j] = &next;
            cout << v[i][j]->x << " " << v[i][j]->y << " " << v[i][j]->objects.size() << "\n";
            cout << "-\n";
        }
    }
    cout << "finished generating\n";
    return v;
}

map::Map::Map(int m, int n) : Map(generate_empty(n, m)) {
    // quick initialization
    // uses an initializer list
}

vector<vector<map::Location*>> map::Map::ChangeCells(int x1, int y1, int x2, int y2, 
vector<vector<map::Location*>> l) {
    for (int i = y1; i <= y2; i ++) {
        for (int j = x1; j <= x2; j ++) {
            map::Location cur = *(l[i - y1][j - x1]);
            cur.chunk = this;
            cur.x = j;
            cur.y = i;
            matrix[i][j] = &cur;
            passable[i][j] = GetPass(matrix[i][j]);
        }
    }
    return matrix;
}

vector<vector<map::Location*>> map::Map::ChangeCells(int x1, int y1, int x2, int y2, 
map::Location* l) {
    return map::Map::ChangeCells(x1, y1, x2, y2, vector<vector<map::Location*>> (y2 - y1 + 1, 
vector<map::Location*> (x2 - x1 + 1, l)));
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

vector<vector<char>> map::Map::GetCharRep() {
    vector<vector<char>> rep (matrix.size(), vector<char> (matrix[0].size(), '?'));
    for (int i = 0; i < matrix.size(); i ++) {
        for (int j = 0; j < matrix[0].size(); j ++) {
            int bestz = -1e9; string bestc = "?";
            cout << matrix[i][j]->objects.size() << "\n";
            for (int k = 0; k < 5; k ++) {
                cout << i << " " << j << "\n";
                Object o = matrix[i][j]->objects[k];
                cout << "AAA\n";
                cout << o.attr["TILE"] << "\n";
                int z; string c = (o.attr["TILE"] != "") ? o.attr["TILE"] : "?";
                try {
                    z = std::stoi(o.attr["ZLEVEL"]);
                }
                catch (...) {
                    z = 0;
                }
                if (z > bestz) bestc = c;
            }
            rep[i][j] = bestc[0];
        }
    }
    return rep;
}