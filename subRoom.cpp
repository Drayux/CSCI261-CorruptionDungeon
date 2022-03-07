/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

/* 
 * File:   subRoom.cpp
 * Author: Drayux
 * 
 * Created on December 1, 2018, 12:17 AM
 */

#include "subRoom.h"
#include "room.h"
#include "roomType.h"

//DEPRICATED CLASS - New system in place
subRoom::subRoom(int _posX, int _posY, roomType _type, int _mrX, int _mrY) : room(_posX, _posY, _type) {
    mainRoomX = _mrX;
    mainRoomY = _mrY;
    
}

int subRoom::getMainRoomX() {
    return mainRoomX;
    
}

int subRoom::getMainRoomY() {
    return mainRoomY;
    
}