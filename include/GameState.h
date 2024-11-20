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
    virtual ~GameState();

    //functions
    void updateKeybinds(const float& deltaTime);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
    void quit();
};
