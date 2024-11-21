#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MenuState.h"
class Game {
private:
    //Variables
    sf :: RenderWindow *window;
    sf :: Event event;
    sf :: Clock clock;
    float deltaTime;

    std :: stack<State*> states;

    //Initialization
    void initWindow();
    void initStates();

public:
    //constructor & destructor
    Game();
    virtual ~Game();
    
    //function
    void flushClock();
    void updateSMFLevents();
    void update();
    void render();
    void run();
};