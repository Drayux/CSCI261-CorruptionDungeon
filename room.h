/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

/* 
 * File:   room.h
 * Author: Drayux
 *
 * Created on November 29, 2018, 2:29 AM
 */

#ifndef ROOM_H
#define ROOM_H

#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "roomType.h"
#include "subRoomType.h"
#include "wallType.h"
#include "player.h"
#include "direction.h"

class room {
public:
    //CONSTRUCTORS
    room(int, int);
    room(int, int, roomType);
    
    //FUNCTIONS
    void draw(RenderWindow&, float, float);
    bool shouldBeRendered(RenderWindow&, float, float);
    //    Getters
    int getPosX();
    int getPosY();
    //int getSizeX();
    //int getSizeY();
    roomType getType();
    bool unstable();
    //bool mainRoom();
    //bool exists();
    
    room& getMainRoom();
    long getSubRoomsSize();
    room& getSubRoom(int);
    
    vector<room> generate(direction);
    
    int getTextureSize();
    int getRenderPositionX(float, int);
    int getRenderPositionY(float, int);
    Color getColor();
    
    //    Setters
    void setColor(Color);
    void setMainRoom(room*);
    
private:
    //CONSTRUCTORS
    room(int, int, roomType, subRoomType);
    
    //VARIABLES
    int posX;             //Location X within the room array
    int posY;             //Location Y within the room array
    
    int minSizeX;
    int minSizeY;
    int sizeX;            //How many array spaces wide the room can be
    int sizeY;            //How many array spaces tall the room can be

    room* mainRoom;       //Pointer to the address of the main room
    
    roomType type;        //The type of room this is
    subRoomType subType;  //The subtype of room this is
    wallType walls[4];      //TODO IMPLEMENT THIS
    bool isUnstable;        //Boolean if the room is stable
    //bool isMainRoom;      //Boolean if the room is a main room
    //bool roomExists;      //If the room does not "exist" it can be overwritten

    vector<room> subRooms;
    
    Texture texture;      //The location of the texture this room uses
    int textureSize;      //How many pixels wide and long one section of room is
    Color color;          //The background color of the room
    
    //FUNCTIONS
    void build();
    
};

#endif

