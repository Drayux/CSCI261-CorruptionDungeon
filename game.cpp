#include <random>
#include <iostream>
#include <Windows.h>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "roomType.h"
#include "dungeon.h"
#include "direction.h"

const float MOVEMENT_SPEED = 2.5;
const float cameraMovementSpeed = 8.0;
const int roomPixelSize = 128;    //WILL BE CHANGED WHEN SETTINGS ARE IMPLEMENTED
const int DESTRUCTION_RANGE = 1;

const bool NOCLIP = false;

const int UPS = 75;  //Updates per second

void game(dungeon& dungeonGame, RenderWindow& window) {
    srand(time(0));

    //Game control variables
    bool freeCamera = false;

    //Controls variables (used to ensure buttons do not get excessively pressed)
    bool middlePressed = false;

    //Generation variables
    int currentRoom[2];  //X, Y coordinates of room player is currently in
    vector<int> outerRooms;      //Array of indicies of dungeon outer rooms
    vector<int> roomsToGenerate;
    vector<room> newRooms;
    float chance;
    int gen = 0;
    int size = 0;
    int roomCount = 1;
    direction dir;

    int upMax;
    int leftMax;
    int downMax;
    int rightMax;

    //Holds further execution of the thread until the window is created
    while (!window.isOpen()) {
        Sleep(100);

    }

    while (window.isOpen()) {
        //MOVEMENT CONTROLS
        /*if (Keyboard::isKeyPressed(Keyboard::Space)) {
            dungeonGame.getRoom(3).setColor(Color(rand() % 255, rand() % 255, rand() % 255));

        }*/
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (!freeCamera) {
                if (NOCLIP) dungeonGame.getPlayer().moveY(-MOVEMENT_SPEED);
                //THE FOLLOWING ELSE-IF MUST COMPARE IN THIS FASHION (this depends on a short circuit as the second part will crash the program with an array out of bounds exception)
                else if (!(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY() - MOVEMENT_SPEED)) < 0
                        /*|| dungeonGame.getRoom(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY() - MOVEMENT_SPEED))).getType() == EMPTY*/))
                    dungeonGame.getPlayer().moveY(-MOVEMENT_SPEED);

            }
            else dungeonGame.moveCameraY(-cameraMovementSpeed);

        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (!freeCamera) {
                if (NOCLIP) dungeonGame.getPlayer().moveX(-MOVEMENT_SPEED);
                //THE FOLLOWING ELSE-IF MUST COMPARE IN THIS FASHION (this depends on a short circuit as the second part will crash the program with an array out of bounds exception)
                else if (!(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX() - MOVEMENT_SPEED), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY())) < 0
                        /*|| dungeonGame.getRoom(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY() - MOVEMENT_SPEED))).getType() == EMPTY*/))
                    dungeonGame.getPlayer().moveX(-MOVEMENT_SPEED);

            }
            else dungeonGame.moveCameraX(-cameraMovementSpeed);

        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            if (!freeCamera) {
                if (NOCLIP) dungeonGame.getPlayer().moveY(MOVEMENT_SPEED);
                //THE FOLLOWING ELSE-IF MUST COMPARE IN THIS FASHION (this depends on a short circuit as the second part will crash the program with an array out of bounds exception)
                else if (!(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY() + MOVEMENT_SPEED)) < 0
                        /*|| dungeonGame.getRoom(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY() + MOVEMENT_SPEED))).getType() == EMPTY*/))
                    dungeonGame.getPlayer().moveY(MOVEMENT_SPEED);

            }

        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (!freeCamera) {
                if (NOCLIP) dungeonGame.getPlayer().moveX(MOVEMENT_SPEED);
                //THE FOLLOWING ELSE-IF MUST COMPARE IN THIS FASHION (this depends on a short circuit as the second part will crash the program with an array out of bounds exception)
                else if (!(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX() + MOVEMENT_SPEED), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY())) < 0
                        /*|| dungeonGame.getRoom(dungeonGame.getRoomIndex(dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()), dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY() + MOVEMENT_SPEED))).getType() == EMPTY*/))
                    dungeonGame.getPlayer().moveX(MOVEMENT_SPEED);

            }
        }

        //NON-MOVEMENT CONTROLS
        //Note zooming is found within the render thread as it only modifies the rendering of the game
        if (!Mouse::isButtonPressed(Mouse::Middle)) middlePressed = false;
        else if (Mouse::isButtonPressed(Mouse::Middle) && !freeCamera && !middlePressed) {
            freeCamera = true;
            middlePressed = true;

        }
        else if (Mouse::isButtonPressed(Mouse::Middle) && freeCamera && !middlePressed) {
            freeCamera = false;
            middlePressed = true;

        }
        //CAMERA MOVEMENT
        if (!freeCamera) {
            dungeonGame.setCameraPosX(dungeonGame.getPlayer().getPosX());
            dungeonGame.setCameraPosY(dungeonGame.getPlayer().getPosY());
            //TODO FREEZE GAME UPDATES WHILE FREECAMERA IS ACTIVE

        }

        //DUNGEON GENERATION
        currentRoom[0] = dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX());
        currentRoom[1] = dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY());

        //Determines direction where rooms need to be generated
        //cout << dungeonGame.getGenerationRangeX(true) - currentRoom[0] << endl;
        if (dungeonGame.getGenerationRangeX(true) - currentRoom[0] < dungeonGame.getRoomsX()) {             //X direction positive
            dir = RIGHT;
            //cout << "test RIGHT" << endl;

        } else if (-(dungeonGame.getGenerationRangeX(false) - currentRoom[0]) < dungeonGame.getRoomsX()) {   //X direction negative
            dir = LEFT;
            //cout << "test LEFT" << endl;

        } else if (dungeonGame.getGenerationRangeY(true) - currentRoom[1] < dungeonGame.getRoomsY()) {       //Y direction positive
            dir = DOWN;
            //cout << "test DOWN" << endl;

        } else if (-(dungeonGame.getGenerationRangeY(false) - currentRoom[1]) < dungeonGame.getRoomsY()) {   //Y direction negative
            dir = UP;
            //cout << "test UP" << endl;

        } else dir = NONE;
        //Select rooms to generate; TODO complete selecting random number of random rooms
        if (dir != NONE) {
            outerRooms = dungeonGame.getOutterRooms(dir);
            //Remove empty room from generation
            for (int i = 0; i < outerRooms.size(); i++) {
                if (dungeonGame.getRoom(outerRooms.at(i)).getType() == EMPTY) outerRooms.erase(outerRooms.begin() + i);

            }
            //Randomize how many rooms to select
            size = outerRooms.size();
            do {
                chance = 2.0 - (4.0 * roomCount - 3.0) / size;
                //cout << chance << endl;
                if (outerRooms.size() == 0) break;
                if (rand() * chance - RAND_MAX <= 0.01) {
                    if (outerRooms.size() > 0) gen = rand() % outerRooms.size();
                    else gen = 0;
                    roomsToGenerate.push_back(outerRooms.at(gen));
                    outerRooms.erase(outerRooms.begin() + gen);

                }
                roomCount += 1;

            } while (chance >= 1.0);
            //cout << "Rooms to generate: " << roomsToGenerate.size() << endl;
            for (int i = 0; i < roomsToGenerate.size(); i++) {
                //cout << "Generating on room: " << roomsToGenerate.at(i) << endl;
                newRooms = dungeonGame.getRoom(roomsToGenerate.at(i)).generate(dir);
                for (int j = 0; j < newRooms.size(); j++) {
                    //if (newRooms.at(j).getType() != EMPTY) dungeonGame.buildRoom(newRooms.at(j));
                    dungeonGame.buildRoom(newRooms.at(j));

                }
                newRooms.clear();
                newRooms.shrink_to_fit();

            }
        }
        roomCount = 1;

        outerRooms.clear();
        outerRooms.shrink_to_fit();
        roomsToGenerate.clear();
        roomsToGenerate.shrink_to_fit();

        //DUNGEON DESTRUCTION (TODO COMPLETE THIS)
        if (dungeonGame.getGenerationRangeX(true) - currentRoom[0] > dungeonGame.getRoomsX() + DESTRUCTION_RANGE) {             //X direction positive
            dir = RIGHT;
            //cout << "test RIGHT" << endl;

        } else if (-(dungeonGame.getGenerationRangeX(false) - currentRoom[0]) > dungeonGame.getRoomsX() + DESTRUCTION_RANGE) {   //X direction negative
            dir = LEFT;
            //cout << "test LEFT" << endl;

        } else if (dungeonGame.getGenerationRangeY(true) - currentRoom[1] > dungeonGame.getRoomsY() + DESTRUCTION_RANGE) {       //Y direction positive
            dir = DOWN;
            //cout << "test DOWN" << endl;

        } else if (-(dungeonGame.getGenerationRangeY(false) - currentRoom[1]) > dungeonGame.getRoomsY() + DESTRUCTION_RANGE) {   //Y direction negative
            dir = UP;
            //cout << "test UP" << endl;

        } else dir = NONE;
        //Select rooms to destruct (TODO ensure room is destroyed if CLOSEST point is out of range
        if (dir != NONE) {
            outerRooms = dungeonGame.getOutterRooms(dir);
            for (int i = outerRooms.size() - 1; i >= 0; i--) {
                dungeonGame.destroyRoom(outerRooms.at(i));
                //cout << "Destroyed room: " << outterRooms.at(i) << endl;

            }
            //Update generated array
            //dungeonGame.moveGenerationRange(dir, false);

        }
//        cout << dungeonGame.getGenerationRangeX(false) << " " << dungeonGame.getGenerationRangeX(true) << "   "
//             << dungeonGame.getGenerationRangeY(false) << " " << dungeonGame.getGenerationRangeY(true) << "   "
//             << dungeonGame.getCurrentRoomX(dungeonGame.getPlayer().getPosX()) << " " << dungeonGame.getCurrentRoomY(dungeonGame.getPlayer().getPosY()) << endl;
        //FINAL ROOM UPDATE
        outerRooms.clear();
        outerRooms.shrink_to_fit();
        roomsToGenerate.clear();
        roomsToGenerate.shrink_to_fit();

        upMax = dungeonGame.getRoom(dungeonGame.getOutterRooms(UP).at(0)).getPosY();
        leftMax = dungeonGame.getRoom(dungeonGame.getOutterRooms(LEFT).at(0)).getPosX();
        downMax = dungeonGame.getRoom(dungeonGame.getOutterRooms(DOWN).at(0)).getPosY();
        rightMax = dungeonGame.getRoom(dungeonGame.getOutterRooms(RIGHT).at(0)).getPosX();

        dungeonGame.setGenerationRangeX(leftMax, rightMax);
        dungeonGame.setGenerationRangeY(upMax, downMax);
        //UPS MANAGEMENT
        Sleep(1000/UPS);

    }
}
