#include "game.h"
//Initialization
void game :: initWindow() {
    this -> window = new sf :: RenderWindow(sf :: VideoMode(1920, 1080), "RPG GAME");
    this -> window -> setFramerateLimit(120);
    this -> window -> setVerticalSyncEnabled(false);
}
void game :: initStates() {
    this -> states.push(new GameState(this -> window));
}

//constructor & destructor
game :: game() {
    this -> initWindow();
    this -> initStates();  
}
game :: ~game() {
    delete this -> window;
    while(!this -> states.empty()) {
        delete this -> states.top();
        this -> states.pop();
    }
}

//function
void game :: flushClock() {
    this -> deltaTime = this -> clock.restart().asSeconds();
}
void game :: updateSMFLevents() {
    while(this -> window -> pollEvent(this -> event)) {
        if(event.type == sf :: Event :: Closed)
            this -> window -> close();
    }
}
void game :: update() {
    this -> updateSMFLevents();
    if(!this -> states.empty())
        this -> states.top() -> update(this -> deltaTime);
}
void game :: render() {
    this -> window -> clear();
    if(!this -> states.empty())
        this -> states.top() -> render(this -> window);
    this -> window -> display();
}
#include<iostream>
void game :: run() {
    while (this -> window -> isOpen()) {
        //std :: cerr << this -> deltaTime << std :: endl;
        this -> flushClock();
        this -> update();
        this -> render();
    }
}
