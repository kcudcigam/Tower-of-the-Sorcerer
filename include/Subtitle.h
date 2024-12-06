#pragma once
#include <SFML/Graphics.hpp>
#include "Resource.h"
class Subtitle {
private:
    //Variables
    Resource* resource;
    sf :: Text text;
    float countdown;
public:
    //constructor & destructor
    Subtitle(Resource* resource);
    virtual ~Subtitle();
    //funtions
    void setFont(const std :: string &file);
    void setPosition(const sf :: Vector2f &position);
    void display(const std :: wstring &sentence, const float &duration);
    void clear();
    void update(const float &deltaTime);
    void render(sf :: RenderTarget* target) const;
};