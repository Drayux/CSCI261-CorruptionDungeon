/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

/* 
 * File:   main.cpp
 * Author: Drayux
 *
 * Created on November 19, 2018, 11:56 PM
 */

#include <iostream>
#include <thread>
using namespace std;

#include "dungeon.h"
#include "render.h"
#include "game.h"

int main() {
    //TODO
    //    Fix crash after a couple minutes of lots of generation (I think it's making a vector larger than memory can hold)
    //    Fix zoom feature such that it is the same speed across different refresh rates (right now: faster refresh rate = faster zoom)
    cout << "Welcome to the Dungeon of the Corrupt!" << endl << endl;
    
    dungeon dungeonGame(4, 4);
    RenderWindow window;
    
    cout << "Dungeon memory address: " << &dungeonGame << endl;
    
    thread renderEnv(render, ref(dungeonGame), ref(window));  //Renders the game
    thread gameEnv(game, ref(dungeonGame), ref(window));      //Handles game events
    
    renderEnv.join();
    gameEnv.join();
    
    cout << "Thread execution complete." << endl;
    
    return 0;
}

