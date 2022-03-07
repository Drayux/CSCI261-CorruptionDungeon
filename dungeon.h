/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

/* 
 * File:   dungeon.h
 * Author: Drayux
 *
 * Created on November 29, 2018, 2:33 AM
 */

#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
using namespace std;

#include <SFML/Window.hpp>

#include "room.h"
#include "player.h"
#include "direction.h"

class dungeon {
public:
    dungeon();
    dungeon(unsigned int, unsigned int);
    
    void buildRoom(room&);
    void destroyRoom(int);
    
    room& getRoom(unsigned int);
    int getRoomIndex(int, int);
    int getCurrentRoomX(int); //Find the active room X-coordinate from a player position
    int getCurrentRoomY(int); //Find the active room Y-coordinate from a player position
    
    vector<room>& getRoomArray();
    int getTotalRooms();
    vector<int> getOutterRooms(direction);
    
    player& getPlayer();
    
    int getRoomsX();
    int getRoomsY();
    
    void moveGenerationRange(direction, bool);
    void setGenerationRangeX(int, int);
    void setGenerationRangeY(int, int);
    
    int getGenerationRangeX(bool);
    int getGenerationRangeY(bool);
    
    float getCameraPosX();
    float getCameraPosY();
    
    void moveCameraX(float);
    void moveCameraY(float);
    
    void setCameraPosX(float);
    void setCameraPosY(float);
    
private:
    int roomsX;              //Range of room direction in X direction (as a radius)
    int roomsY;              //Range of room direction in Y direction (as a radius)
    
    int roomsGeneratedX[2];  //Min and max coordinates of generated rooms in X
    int roomsGeneratedY[2];  //Min and max coordinates of generated rooms in Y
    
    float cameraPosX;        //X position of the camera
    float cameraPosY;        //Y position of the camera
    
    vector<room> rooms;
    player player1;   //NOTE at some point this might be different for multi-player capabilities
    
    void generate(int, int, unsigned int, unsigned int);  //DEPRECATED

};

#endif 

