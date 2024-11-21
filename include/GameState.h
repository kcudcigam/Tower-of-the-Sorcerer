#pragma once
#include "State.h"
#include "Entity.h"
#include <iostream>
class GameState : public State {
private:
    //Variables
    Entity player;
public:
    //constructor & destructor
    GameState(sf :: RenderWindow* window);
    ~GameState();

    //functions
    void checkForQuit();
    void update(const float& deltaTime);
    void render();
};
