#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
class state {
private:
    //Variables
    sf :: RenderWindow* window;
    std :: vector<sf :: Texture> texture;
public:
    //constructor & destructor
    state(sf :: RenderWindow* window);
    virtual ~state();

    //funtions
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf :: RenderTarget* target = nullptr) = 0;
    virtual void end() = 0;
};