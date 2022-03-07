/* 
 * File:   subRoom.h
 * Author: Drayux
 *
 * Created on December 1, 2018, 12:17 AM
 */

#ifndef SUBROOM_H
#define SUBROOM_H

#include "room.h"
#include "roomType.h"

//DEPRICATED CLASS - New system in place
class subRoom : public room {
public:
    subRoom(int, int, roomType, int, int);

    int getMainRoomX();
    int getMainRoomY();

private:
    int mainRoomX;
    int mainRoomY;

};

#endif /* SUBROOM_H */
