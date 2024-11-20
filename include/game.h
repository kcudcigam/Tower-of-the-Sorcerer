#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "GameState.h"
class game {
private:
    //Variables
    sf :: RenderWindow *window;
    sf :: Event event;
    sf :: Clock clock;
    float deltaTime;

    std :: stack<state*> states;

    //Initialization
    void initWindow();
    void initStates();

public:
    //constructor & destructor
    game();
    virtual ~game();
    
    //function
    void flushClock();
    void updateSMFLevents();
    void update();
    void render();
    void run();
};