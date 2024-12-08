#include "Game.h"

//Game
Game :: Game() : window(sf :: VideoMode(1280, 960), "The Sorcerer") {
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    states.push(new MenuState(&window, &states));
}
Game :: ~Game() {
    while(!states.empty()) {
        delete states.top();
        states.pop();
    }
}
void Game :: update() {
    while(window.pollEvent(event)) {
        if(event.type == sf :: Event :: Closed) window.close();
    }
    deltaTime = clock.restart().asSeconds();
    if(!states.empty()) {
        states.top() -> update(deltaTime);
        if(states.top() -> end()) {
            delete states.top();
            states.pop();
        }
    }
    else window.close();
}
void Game :: render() {
    window.clear();
    if(!states.empty()) states.top() -> render(&window);
    window.display();
}
void Game :: run() {
    while (window.isOpen()) update(), render();
}
