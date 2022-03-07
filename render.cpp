/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>    //For testing
using namespace std;

#include "room.h"
#include "dungeon.h"

const int WINDOW_X = 800;
const int WINDOW_Y = 600;

const int ZOOM_MIN = 500;    //Minimum zoom scaling (the larger the number, the slower the game re-scales)
const int ZOOM_MAX = 1300;   //Maximum zoom scaling (suggested double ZOOM_MIN)
const int ZOOM_TICKS = 8;

///////////////////////////////////////////////////
//                     TODO
// - Frame blending
// - ~~Render only elements on-screen~~
///////////////////////////////////////////////////

void render(dungeon& dungeonGame, RenderWindow& window) {
    window.create(VideoMode(WINDOW_X, WINDOW_Y), "Corruption Dungeon");
    View newView = window.getView();
    
    int scale = ZOOM_MAX;
    int scaleFactor = (ZOOM_MAX + ZOOM_MIN) / 2;
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            
            if (event.type == Event::Resized) {
                //Resizes the rooms based on the window WIDTH
                newView.setSize((WINDOW_X * float(ZOOM_MAX)) / scale, ((WINDOW_X * float(ZOOM_MAX)) / (window.getSize().x * scale) * window.getSize().y));
                newView.setCenter(newView.getSize().x/2, newView.getSize().y/2);
                
                window.setView(newView);
                
            }
            
            if (event.type == Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0 && scaleFactor < ZOOM_MAX) scaleFactor += ((ZOOM_MAX - ZOOM_MIN) / ZOOM_TICKS);
                else if (event.mouseWheelScroll.delta < 0 && scaleFactor > ZOOM_MIN) scaleFactor += -((ZOOM_MAX - ZOOM_MIN) / ZOOM_TICKS);
                
            }
        }

        //Adds smoothness to mouse scrolling
        if (scale < scaleFactor) {
            scale += 1;
                
            newView.setSize((WINDOW_X * float(ZOOM_MAX)) / scale, ((WINDOW_X * float(ZOOM_MAX)) / (window.getSize().x * scale) * window.getSize().y));
            newView.setCenter(newView.getSize().x/2, newView.getSize().y/2);
            window.setView(newView);
                
            //cout << scaleFactor << endl;
                
        } else if (scale > scaleFactor) {
            scale += -1;
                
            newView.setSize((WINDOW_X * float(ZOOM_MAX)) / scale, ((WINDOW_X * float(ZOOM_MAX)) / (window.getSize().x * scale) * window.getSize().y));
            newView.setCenter(newView.getSize().x/2, newView.getSize().y/2);
            window.setView(newView);
                
            //cout << scaleFactor << endl;
                
        }
        
        //cout << window.getSize().x << "   " << window.getSize().y << endl;
        //cout << window.getView().getSize().x << "   " << window.getView().getSize().y << endl;
        //cout << window.getView().getCenter().x << "   " << window.getView().getCenter().x << endl;
        
        //CLEAR WINDOW
        window.clear();
        
        //DRAW OBJECTS
        //Rooms
        for (int i = 0; i < dungeonGame.getTotalRooms(); i++) {
            if (dungeonGame.getRoom(i).shouldBeRendered(window, dungeonGame.getCameraPosX(), dungeonGame.getCameraPosY())) {
                dungeonGame.getRoom(i).draw(window, dungeonGame.getCameraPosX(), dungeonGame.getCameraPosY());
        
            }
        }
        //Player
        dungeonGame.getPlayer().draw(window, dungeonGame.getCameraPosX(), dungeonGame.getCameraPosY());
        
        //RENDER FRAME
        window.display();
    }
    
}