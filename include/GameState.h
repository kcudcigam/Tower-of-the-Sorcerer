#pragma once
#include <iostream>
#include "State.h"
#include "Player.h"
#include "Tilemap.h"
#include "Subtitle.h"

class GameState : public State {
private:
    //Variables
    Tilemap map;
    Subtitle subtitle;
public:
    //constructor & destructor
    GameState(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource, const std :: string &map);
    ~GameState();

    //functions
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target = nullptr);
};
