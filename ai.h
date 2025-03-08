#pragma once // if the file is included multiple times, only one duplicate will exist.

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "map.h"

namespace ai {
    class Action {
        public:
        // constructor here
        std::string name;
        double weight;

    };
    extern std::vector<Action> actions;
    class Motivation {
        public:
        // constructor here
        std::string name;
        std::vector<std::pair<std::string, double>> related; // the names of related actions and how much the motivation affects them
    };
    class Decisionmaker {
        public:
            // constructor here

            std::map<std::string, Action> possible;
            std::vector<Motivation> motivations;
            Action getAction();
    };
}
