/* 
 * File:   room.cpp
 * Author: Drayux
 *
 * Created on November 29, 2018, 2:29 AM
 */

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>    //For testing
#include <random>      //Will be used to randomize room sizes
#include <vector>
using namespace std;

#include "room.h"
#include "roomType.h"
#include "subRoomType.h"
#include "player.h"
#include "direction.h"
#include "util.h"

const int roomPixelSize = 128;    //WILL BE CHANGED WHEN SETTINGS ARE IMPLEMENTED

room::room(int _posX, int _posY) {
    posX = _posX;
    posY = _posY;

    type = EMPTY;
    subType = MAIN;

    mainRoom = this;
    textureSize = roomPixelSize;

    this->build();

}
room::room(int _posX, int _posY, roomType _type) {
    posX = _posX;
    posY = _posY;

    type = _type;
    subType = MAIN;

    mainRoom = this;
    textureSize = roomPixelSize;

    this->build();

}
//Private constructor, subrooms should be generated ONLY by main rooms
room::room(int _posX, int _posY, roomType _type, subRoomType _subType) {
    posX = _posX;
    posY = _posY;

    type = _type;
    subType = _subType;

    textureSize = roomPixelSize;

}

//Recursively assigns texture, size, element properties, and background color to a room and corresponding subrooms
void room::build() {
    //NOTE Eventually change the BG color to be the "biome" as opposed to a base color
    switch (type) {
        case START:
            color = Color(200, 20, 20);    //Red
            //roomExists = true;

            if (subType == MAIN) {
                minSizeX = 3;
                minSizeY = 3;

                sizeX = 3;
                sizeY = 3;

            }
            break;
        case HALLWAY:
            color = Color(190, 130, 40);   //Brown
            //roomExists = true;

            if (subType == MAIN) {
                minSizeX = 1;
                minSizeY = 1;

                sizeX = 1;
                sizeY = 1;

            }
            break;
        case JAIL:
            color = Color(130, 130, 130);  //Gray
            //roomExists = true;

            //Jail generation is directional (seen below w/in subroom generation)
            if (subType == MAIN) {
                minSizeX = 1; //3;
                minSizeY = 1; //3;

                sizeX = 1; //10;
                sizeY = 1; //10;

            }
            break;
        case TREASURE_ROOM:
            color = Color(225, 200, 45);   //Gold
            //roomExists = true;


            if (subType == MAIN) {
                minSizeX = 1; //2;
                minSizeY = 1; //2;

                sizeX = 1; //2;
                sizeY = 1; //2;

            }
            break;
        default:  //roomType::EMPTY
            color = Color::Black; //Color(rand() % 255, rand() % 255, rand() % 255);
            //roomExists = false;

            minSizeX = 1;
            minSizeY = 1;

            sizeX = 1;
            sizeY = 1;
            break;
    }

    //Open walls

    //Open doors

    //Texture assignment
        //todo texture assignment
        //todo path texture assignment

    //Subroom generation
    /*if (subType ==  MAIN && type == JAIL) {            //Jail cell room


    } else*/ if (subType == MAIN) {                      //Normal, square rooms
        int maxX;
        int maxY;

        if (sizeX > 1) maxX = rand() % (sizeX - minSizeX + 1) + (minSizeX);
        else maxX = 1;
        if (sizeY > 1) maxY = rand() % (sizeY - minSizeY + 1) + (minSizeY);
        else maxY = 1;

        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                if (i == 0 && j == 0) continue;   //Prevents duplication of main room

                //~~Calculate subtype~~
                //Special room of width or length of 1
                if (sizeX ==  1 || sizeY == 1) {
                    room subRoom(posX + i, posY + j, type, MIDDLE);
                    subRoom.setMainRoom(mainRoom);
                    //TODO make appropriate side open
                    subRoom.build();
                    subRooms.push_back(subRoom);
                    continue;

                }

                //Most rooms
                subRoomType _subType;
                if (i == 0) {
                    if (j == maxY - 1) _subType = CORNER_DOWN_LEFT;
                    else _subType = WALL_WEST;

                } else if (i == maxX - 1) {
                    if (j == 0) _subType = CORNER_UP_RIGHT;
                    else if (j == maxY - 1) _subType = CORNER_DOWN_RIGHT;
                    else _subType = WALL_EAST;

                } else {
                    if (j == 0) _subType = WALL_NORTH;
                    else if (j == maxY - 1) _subType = WALL_SOUTH;
                    else _subType =  MIDDLE;

                }
                room subRoom(posX + i, posY + j, type, _subType);
                subRoom.build();
                subRooms.push_back(subRoom);

            }
        }
    }
}

void room::draw(RenderWindow& window, float _cPosX, float _cPosY) {
    RectangleShape shape(Vector2f(textureSize, textureSize));

    shape.setFillColor(color);
    shape.setPosition(this->getRenderPositionX(_cPosX, window.getView().getSize().x), this->getRenderPositionY(_cPosY, window.getView().getSize().y));

    window.draw(shape);

}

//Checks if the room is on-screen and has elements to be rendered
bool room::shouldBeRendered(RenderWindow& _window, float cameraPosX, float cameraPosY) {
    if (this->getRenderPositionX(cameraPosX, _window.getView().getSize().x) >= -this->getTextureSize()
        && this->getRenderPositionX(cameraPosX, _window.getView().getSize().x) < _window.getView().getSize().x
        && this->getRenderPositionY(cameraPosY, _window.getView().getSize().y) >= -this->getTextureSize()
        && this->getRenderPositionY(cameraPosY, _window.getView().getSize().y) < _window.getView().getSize().y
        && (this->getType() != EMPTY || this->unstable())) {
        return true;

    }
    return false;
}

int room::getPosX() {
    return posX;

}

int room::getPosY() {
    return posY;

}

/*int room::getSizeX() {
    return sizeX;

}

int room::getSizeY() {
    return sizeY;

}*/

roomType room::getType() {
    return type;

}

bool room::unstable() {
    return isUnstable;

}

/*bool room::mainRoom() {
    return isMainRoom;

}

bool room::exists() {
    return roomExists;

}*/

room& room::getMainRoom() {
    return *mainRoom;

}

long room::getSubRoomsSize() {
    return subRooms.size();

}

room& room::getSubRoom(int index) {
    return subRooms.at(index);

}

vector<room> room::generate(direction dir) {
    //Create test room (random favoring hallway or type declared by room)
    //Choose direction to generate test room (random favoring dir)
        //Check if room can be placed in that direction
            //Make sure this is on bound of room and not main
        //If not re-choose direction
    //If this fails, make the new room a hallway, rinse and repeat
    //If this fails, return room of empty type

    vector<room> newRooms;
    vector<bool> genDirs;
    vector<float> roomChance;

    int basePosX = posX;
    int basePosY = posY;

    switch (type) {
        case HALLWAY:
            genDirs = variedRand({0.7, 0.3, 0.3});   //dir, not opposite(dir), not opposite(dir)
            roomChance = {0.0, 0.0, 0.7, 0.295, 0.005};
            break;
        case JAIL:
            genDirs = variedRand({1.0, 1.0, 1.0});
            roomChance = {0.0, 0.0, 0.8, 0.05, 0.15};
            break;
        case TREASURE_ROOM:
            genDirs = variedRand({0.25, 0.0, 0.0});
            roomChance = {0.0, 0.0, 1.0, 0.0, 0.0};
            break;
        default:
            genDirs.push_back(false);
            genDirs.push_back(false);
            genDirs.push_back(false);

    }
//    for (int i = 0; i < genDirs.size(); i++) {
//        cout << genDirs.at(i) << endl;
//
//    }

    switch (dir) {
        case UP:
            // UP, LEFT, RIGHT
            if (genDirs.at(0)) newRooms.push_back(room(basePosX, basePosY - 1, roomType(weightedRand(roomChance))));
            if (genDirs.at(1)) newRooms.push_back(room(basePosX - 1, basePosY, roomType(weightedRand(roomChance))));
            if (genDirs.at(2)) newRooms.push_back(room(basePosX + 1, basePosY, roomType(weightedRand(roomChance))));
            break;
        case LEFT:
            // LEFT, DOWN, UP
            if (genDirs.at(0)) newRooms.push_back(room(basePosX - 1, basePosY, roomType(weightedRand(roomChance))));
            if (genDirs.at(1)) newRooms.push_back(room(basePosX, basePosY - 1, roomType(weightedRand(roomChance))));
            if (genDirs.at(2)) newRooms.push_back(room(basePosX, basePosY + 1, roomType(weightedRand(roomChance))));
            break;
        case DOWN:
            // DOWN, RIGHT, LEFT
            if (genDirs.at(0)) newRooms.push_back(room(basePosX, basePosY + 1, roomType(weightedRand(roomChance))));
            if (genDirs.at(1)) newRooms.push_back(room(basePosX + 1, basePosY, roomType(weightedRand(roomChance))));
            if (genDirs.at(2)) newRooms.push_back(room(basePosX - 1, basePosY, roomType(weightedRand(roomChance))));
            break;
        case RIGHT:
            // RIGHT, UP, DOWN
            if (genDirs.at(0)) newRooms.push_back(room(basePosX + 1, basePosY, roomType(weightedRand(roomChance))));
            if (genDirs.at(1)) newRooms.push_back(room(basePosX, basePosY - 1, roomType(weightedRand(roomChance))));
            if (genDirs.at(2)) newRooms.push_back(room(basePosX, basePosY + 1, roomType(weightedRand(roomChance))));
            break;

    }
    return newRooms;
}

int room::getTextureSize() {
    return textureSize;

}

int room::getRenderPositionX(float cPosX, int windowSizeX) {
    return textureSize*posX + windowSizeX/2 - textureSize/2 - cPosX;

}

int room::getRenderPositionY(float cPosY, int windowSizeY) {
    return textureSize*posY + windowSizeY/2 - textureSize/2 - cPosY;

}

Color room::getColor() {
    return color;

}

void room::setMainRoom(room* _mr) {
    mainRoom = _mr;

}

void room::setColor(Color _color) {
    color = _color;

}
