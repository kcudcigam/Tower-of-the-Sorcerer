#include "Game.h"
extern Resource resource;
extern Subtitle subtitle;

//Game
Game :: Game() : window(sf :: VideoMode(1280, 720), "The Sorcerer") {
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    resource.loadFrom("../resource");
    subtitle.setFont("pixel.ttf");
    subtitle.setPosition({window.getSize().x / 2.f, window.getSize().y - 100.f});
    states.setMenu(new MenuState(&window, &states));
}
Game :: ~Game() {

}
void Game :: update() {
    while(window.pollEvent(event)) {
        if(event.type == sf :: Event :: Closed) window.close();
    }
    deltaTime = clock.restart().asSeconds();
    states.top() -> update(deltaTime);
}
void Game :: render() {
    window.clear();
    states.top() -> render(&window);
    window.display();
}
void Game :: run() {
    while (window.isOpen()) update(), render();
}
