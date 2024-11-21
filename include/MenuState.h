#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameState.h"
class MenuState : public State {
private:
    //Variables
    sf :: RectangleShape shape;
public:
    //constructor & destructor
    MenuState(sf :: RenderWindow* window, std :: stack<State*>* states);
    ~MenuState();

    //functions
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target = nullptr);
};
