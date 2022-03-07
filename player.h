/* 
 * File:   player.h
 * Author: Drayux
 *
 * Created on November 30, 2018, 12:40 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"

class player {
public:
    player();

    float getPosX();
    float getPosY();

    bool canMove(direction); //TODO complete this

    int getRenderPositionX(float, int);
    int getRenderPositionY(float, int);

    void draw(RenderWindow&, float, float);

    void moveX(float);
    void moveY(float);

private:
    float posX;
    float posY;

    bool playerCanMove[4]; //Up, left, down, right

    Texture texture;
    int textureSizeX;
    int textureSizeY;

};

#endif
