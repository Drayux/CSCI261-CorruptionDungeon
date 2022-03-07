/* 
 * File:   player.cpp
 * Author: Drayux
 *
 * Created on November 30, 2018, 12:40 PM
 */

#include <SFML/Graphics.hpp>
using namespace sf;

#include "player.h"

player::player() {
    posX = 0;
    posY = 0;

    textureSizeX = 15;
    textureSizeY = 25;

}

float player::getPosX() {
    return posX;

}

float player::getPosY() {
    return posY;

}

int player::getRenderPositionX(float _cPosX, int windowSizeX) {
    return posX + windowSizeX/2 - textureSizeX/2 - _cPosX;

}

int player::getRenderPositionY(float _cPosY, int windowSizeY) {
    return posY + windowSizeY/2 - textureSizeY/2 - _cPosY;

}

void player::draw(RenderWindow& window, float _cPosX, float _cPosY) {
    RectangleShape shape(Vector2f(textureSizeX, textureSizeY));

    shape.setFillColor(Color::White);
    shape.setPosition(this->getRenderPositionX(_cPosX, window.getView().getSize().x), this->getRenderPositionY(_cPosY, window.getView().getSize().y));

    window.draw(shape);

}

void player::moveX(float x) {
    posX += x;

}

void player::moveY(float y) {
    posY += y;

}
