#include "Game.h"
//Initialization
void Game :: initWindow() {
    this -> window = new sf :: RenderWindow(sf :: VideoMode(1280, 640), "The Sorcerer");
    this -> window -> setFramerateLimit(120);
    this -> window -> setVerticalSyncEnabled(false);
}
void Game :: initStates() {
    this -> states.push(new MenuState(this -> window, &this -> states, &this -> resource));
}

//constructor & destructor
Game :: Game() : resource("..\\resource") {
    this -> initWindow();
    this -> initStates();
}
Game :: ~Game() {
    delete this -> window;
    while(!this -> states.empty()) {
        delete this -> states.top();
        this -> states.pop();
    }
}

//function
void Game :: flushClock() {
    this -> deltaTime = this -> clock.restart().asSeconds();
}
void Game :: updateSMFLevents() {
    while(this -> window -> pollEvent(this -> event)) {
        if(event.type == sf :: Event :: Closed)
            this -> window -> close();
    }
}
void Game :: update() {
    this -> flushClock();
    this -> updateSMFLevents();
    if(!this -> states.empty()) {
        this -> states.top() -> update(this -> deltaTime);
        if(this -> states.top() -> end()) {
            delete this -> states.top();
            this -> states.pop();
        }
    }
    else this -> window -> close();
}
void Game :: render() {
    this -> window -> clear();
    if(!this -> states.empty())
        this -> states.top() -> render();
    this -> window -> display();
}
void Game :: run() {
    while (this -> window -> isOpen()) {
        this -> update();
        this -> render();
    }
}
