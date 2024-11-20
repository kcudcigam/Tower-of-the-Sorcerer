#pragma once
#include "state.h"
#include<iostream>
class GameState : public state {
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
