#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameState.h"
#include "Subtitle.h"
class MenuState : public State {
private:
    //Variables
    sf :: RectangleShape background;
    sf :: Texture backgroundTexture;
    Subtitle subtitle;

public:
    //constructor & destructor
    MenuState(sf :: RenderWindow* window, std :: stack<State*>* states, Resource* resource);
    ~MenuState();

    //functions
    void checkForQuit();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target = nullptr);
};
