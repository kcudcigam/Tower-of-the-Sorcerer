#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
class state {
private:
    //Variables
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
    bool isQuit;
public:
    //constructor & destructor
    state(sf :: RenderWindow* window);
    virtual ~state();
    //funtions
    const bool& checkQuit() const;
    virtual void updateQuit();
    virtual void updateKeybinds(const float& deltaTime) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target = nullptr) = 0;
    virtual void quit() = 0;
};