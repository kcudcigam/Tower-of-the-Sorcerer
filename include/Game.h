#pragma once
#include "SFML/Graphics.hpp"
#include "Subtitle.h"
#include "State.h"

class Game {
private:
    sf :: RenderWindow window;
    sf :: Event event;
    sf :: Clock clock;
    sf :: Texture loadingTexture;
    float deltaTime;
    Stack<State> states;
public:
    Game();
    virtual ~Game();
    void update();
    void render();
    void run();
};