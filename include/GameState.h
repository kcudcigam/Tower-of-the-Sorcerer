#pragma once
#include <iostream>
#include "State.h"
#include "Entity.h"

class GameState : public State {
private:
    //Variables
    Entity player;
public:
    //constructor & destructor
    GameState(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource);
    ~GameState();

    //functions
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target = nullptr);
};
