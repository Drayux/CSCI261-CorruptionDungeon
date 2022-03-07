/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

/* 
 * File:   dungeon.cpp
 * Author: Drayux
 * 
 * Created on November 29, 2018, 2:33 AM
 */

#include <vector>
#include <random>
#include <iostream>
using namespace std;

#include <SFML/Window.hpp>

#include "dungeon.h"
#include "room.h"
#include "roomType.h"
#include "direction.h"

const int roomPixelSize = 128; //TODO MAKE THIS PART OF SETTINGS (three source files use this)

dungeon::dungeon() {
    roomsX = 3;
    roomsY = 3;
    
    //TODO make hallway starts as a part of the start room generation
    //this->generate(getPlayer().getPosX(), getPlayer().getPosY(), roomsX, roomsY);
    room startRoom(-1, -1, START);
    this->buildRoom(startRoom);
    
    room hallwayNorth(0, 2, HALLWAY);
    this->buildRoom(hallwayNorth);
    
    room hallwayEast(2, 0, HALLWAY);
    this->buildRoom(hallwayEast);
    
    room hallwaySouth(0, -2, HALLWAY);
    this->buildRoom(hallwaySouth);
    
    room hallwayWest(-2, 0, HALLWAY);
    this->buildRoom(hallwayWest);
    
    this->setGenerationRangeX(-2, 2);
    this->setGenerationRangeY(-2, 2);
    
}

dungeon::dungeon(unsigned int _x, unsigned int _y) {
    roomsX = _x;
    roomsY = _y;
    
    //this->generate(getPlayer().getPosX(), getPlayer().getPosY(), roomsX, roomsY);
    room startRoom(-1, -1, START);
    this->buildRoom(startRoom);
    
    room hallwayNorth(0, 2, HALLWAY);
    this->buildRoom(hallwayNorth);
    
    room hallwayEast(2, 0, HALLWAY);
    this->buildRoom(hallwayEast);
    
    room hallwaySouth(0, -2, HALLWAY);
    this->buildRoom(hallwaySouth);
    
    room hallwayWest(-2, 0, HALLWAY);
    this->buildRoom(hallwayWest);
    
    this->setGenerationRangeX(-2, 2);
    this->setGenerationRangeY(-2, 2);
    
}

//DEPRECATED - Generates rooms from the specified position, increasing range in either direction
void dungeon::generate(int _posX, int _posY, unsigned int _rangeX, unsigned int _rangeY) {
    cerr << "Use of deprecated function: dungeon::generate()" << endl;
    return;  //Function replaced by different generation method
    /*int roomIndex;
    
    for (int i = _posX; i < _rangeX + _posX; i++) {
        for (int j = _posY; j < _rangeY + _posY; j++) {
            roomIndex = this->getRoomIndex(i, j);
            if (roomIndex == -1) {
                room newRoom(i, j, roomType(rand() % 4));
                rooms.push_back(newRoom);
                //Subroom generation
                for (int k = 0; k < newRoom.getSizeX() - 1; k++) {
                    for (int l = 0; l < newRoom.getSizeY() - 1; l++) {
                        rooms.push_back(subRoom(newRoom.getPosX() + k, newRoom.getPosY() + l, newRoom.getType(), newRoom.getPosX(), newRoom.getPosY()));
            
                    }
                }
            }
        }
    }*/
}

void dungeon::buildRoom(room& _room) {
    room* temp = &_room;
    
    try {
        rooms.push_back(_room);
        for (int i = 0; i < _room.getSubRoomsSize(); i++) {
            rooms.push_back(_room.getSubRoom(i));//cout << "Built subroom: " << &_room.getSubRoom(i) << " in the dungeon array at index: " << i << endl;
            //cout << "Built subroom: " << &(rooms.back().getSubRoom(i)) << endl;
            //cout << "Built subroom: " << &_room.getSubRoom(i) << " in the dungeon array at index: " << i << endl;
        
        }
        cout << "Built room: " << &(rooms.back()) << endl;
        
    } catch (const exception& e) {
        cerr << "Failed building room: " << temp << endl;
        
    }
}

void dungeon::destroyRoom(int i) {
//    for (int j = rooms.at(i).getSubRoomsSize(); j > 0; j--) {
//        rooms.erase(rooms.begin() + i + j);
//        
//    }
    room* temp = &(rooms.at(i));
    
    try {
        rooms.erase(rooms.begin() + i);
        rooms.shrink_to_fit();
        
        cout << "Destroyed room: " << temp << endl;
        
    } catch (const exception& e) {
        cerr << "Failed destroying room: " << temp << endl;
        
    }
    
}

room& dungeon::getRoom(unsigned int index) {
    return rooms.at(index);
    
}

int dungeon::getRoomIndex(int arrayPosX, int arrayPosY) {
    for (int i = 0; i < rooms.size(); i++) {
        //cout << "Index: " << i << endl;
        if (rooms.at(i).getPosX() == arrayPosX && rooms.at(i).getPosY() == arrayPosY)
            return i;
        
    }
    return -1;
    
}

int dungeon::getCurrentRoomX(int pPosX) {
    if (pPosX >= -roomPixelSize/2) return (pPosX + roomPixelSize/2) / roomPixelSize;
    return (pPosX - roomPixelSize/2) / roomPixelSize;
    
}

int dungeon::getCurrentRoomY(int pPosY) {
    if (pPosY >= -roomPixelSize/2) return (pPosY + roomPixelSize/2) / roomPixelSize;
    return (pPosY - roomPixelSize/2) / roomPixelSize;
    
}

vector<room>& dungeon::getRoomArray() {
    return rooms;
    
}

int dungeon::getTotalRooms() {
    //cerr << "Use of deprecated function: dungeon::getTotalRooms()" << endl;
    return rooms.size();
    
}

//TODO factor in certain rooms having certain subrooms that cannot be generated
vector<int> dungeon::getOutterRooms(direction dir) {
    int coord;      //Determined by the direction of generation
    bool vertical;  //Direction of coord
    vector<int> outterRooms;
    
    switch (dir) {
        case UP:
            vertical = true;
            for (int i = 0; i < rooms.size(); i++) {
                if (i == 0) coord = rooms.at(i).getPosY();
                else if (rooms.at(i).getPosY() < coord) coord = rooms.at(i).getPosY();
                
            }
            break;
        case LEFT:
            vertical = false;
            for (int i = 0; i < rooms.size(); i++) {
                if (i == 0) coord = rooms.at(i).getPosX();
                else if (rooms.at(i).getPosX() < coord) coord = rooms.at(i).getPosX();
                
            }
            break;
        case DOWN:
            vertical = true;
            for (int i = 0; i < rooms.size(); i++) {
                if (i == 0) coord = rooms.at(i).getPosY();
                else if (rooms.at(i).getPosY() > coord) coord = rooms.at(i).getPosY();
                
            }
            break;
        case RIGHT:
            vertical = false;
            for (int i = 0; i < rooms.size(); i++) {
                if (i == 0) coord = rooms.at(i).getPosX();
                else if (rooms.at(i).getPosX() > coord) coord = rooms.at(i).getPosX();
                
            }
            break;
    }
    for (int i = 0; i < rooms.size(); i++) {
        if (vertical && rooms.at(i).getPosY() == coord) outterRooms.push_back(i);
        else if (!vertical && rooms.at(i).getPosX() == coord) outterRooms.push_back(i); 
        
    }
    return outterRooms;
}

player& dungeon::getPlayer() {
    return player1;
    
}

int dungeon::getRoomsX() {
    return roomsX;
    
}

int dungeon::getRoomsY() {
    return roomsY;
    
}

void dungeon::moveGenerationRange(direction dir, bool additive) {
    switch (dir) {
        case UP:    //As though dungeon shifts upward from its current position
            if (additive) roomsGeneratedY[0] += -1;
            else roomsGeneratedY[0] += 1;
            break;
        case LEFT:  //As though dungeon shifts left from its current position
            if (additive) roomsGeneratedX[0] += -1;
            else roomsGeneratedX[0] += 1;
            break;
        case DOWN:  //As though dungeon shifts downward from its current position
            if (additive) roomsGeneratedY[1] += 1;
            else roomsGeneratedY[1] += -1;
            break;
        case RIGHT: //As though dungeon shifts right from its current position
            if (additive) roomsGeneratedX[1] += 1;
            else roomsGeneratedX[1] += -1;
            break;
        
    }
}

void dungeon::setGenerationRangeX(int min, int max) {
    roomsGeneratedX[0] = min;
    roomsGeneratedX[1] = max;
    
}

void dungeon::setGenerationRangeY(int min, int max) {
    roomsGeneratedY[0] = min;
    roomsGeneratedY[1] = max;
    
}

int dungeon::getGenerationRangeX(bool max) {
    if (max) return roomsGeneratedX[1];
    return roomsGeneratedX[0];
    
}

int dungeon::getGenerationRangeY(bool max) {
    if (max) return roomsGeneratedY[1];
    return roomsGeneratedY[0];
    
}

float dungeon::getCameraPosX() {
    return cameraPosX;
    
}

float dungeon::getCameraPosY() {
    return cameraPosY;
    
}

void dungeon::moveCameraX(float x) {
    cameraPosX += x;
    
}

void dungeon::moveCameraY(float y) {
    cameraPosY += y;
    
}

void dungeon::setCameraPosX(float _cPosX) {
    cameraPosX = _cPosX;
    
}

void dungeon::setCameraPosY(float _cPosY) {
    cameraPosY = _cPosY;
    
}