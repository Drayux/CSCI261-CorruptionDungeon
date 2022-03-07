/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

#include <SFML/Window.hpp>
using namespace sf;

#include <iostream>
#include <random>
#include <vector>
using namespace std;

#include "direction.h"

const int roomWidth = 8; //THIS WILL CHANGE LATER WHEN SETTINGS ARE IMPLIMENTED

/* int getRoomArraySize(Window window) {      //How many pixels (X and Y) each unit of room will take up (varies by width of the window)
    return window.getSize().x / roomWidth;
    
}*/

int weightedRand(vector<float> weights) {
    float total = 0;
    int randValue = rand();
    
    for (int i = 0; i < weights.size(); i++) {
        total += weights.at(i);
        
    }
    for (int i = 0; i < weights.size(); i++) {
        weights.at(i) /= total;
        //cout << "Weight of " << i << ": " << vars.at(i) << endl;
        
    }
    for (int i = 0; i < weights.size(); i++) {
        randValue -= int(weights.at(i)*RAND_MAX + 0.1);
        if (randValue < 0) return i;
        
    }
    return -1;
}

vector<bool> variedRand(vector<float> vars) {
    vector<bool> successVals;
    
    for (int i = 0; i < vars.size(); i++) {
        if (rand() - RAND_MAX * vars.at(i) <= 0) {
            successVals.push_back(true);
            
        }
        else successVals.push_back(false);
        
    }
    return successVals;
}

direction getOppositeDirection(direction _dir) {
    switch (_dir) {
        case UP:
            return DOWN;
        case LEFT:
            return RIGHT;
        case DOWN:
            return UP;
        case RIGHT:
            return LEFT;
        default:
            return NONE;
            
    }
}