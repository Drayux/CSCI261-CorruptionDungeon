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
