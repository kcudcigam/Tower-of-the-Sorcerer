#include "Game.h"
extern Resource resource;
extern Subtitle subtitle;

//Game
Game :: Game() : window(sf :: VideoMode(1280, 960), "The Sorcerer") {
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.clear();
    
    sf :: RectangleShape background;
    loadingTexture.loadFromFile("../resource/image/background/loading-background.png");
    background.setSize({1280, 960});
    background.setTexture(&loadingTexture);
    window.draw(background);
    window.display();
    resource.loadFrom("../resource");
    subtitle.setFont("OPPOSans-H-2.ttf");
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
    if(window.getSize() != sf :: Vector2u(1280, 960)) window.setSize(sf :: Vector2u(1280, 960));
    window.clear();
    states.top() -> render(&window);
    window.display();
}
void Game :: run() {
    deltaTime = clock.restart().asSeconds();
    while (window.isOpen()) update(), render();
}
