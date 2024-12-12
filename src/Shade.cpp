#include "Shade.h"

Shade :: Shade(const float &duration, const bool &lighter) : duration(duration), lighter(lighter) {
    reset();
}
void Shade :: reset() {
    paused = false;
    if(lighter) background.setFillColor(sf :: Color :: Black), alpha = 255.f;
    else background.setFillColor(sf :: Color :: Transparent), alpha = 0.f;
}
Shade :: ~Shade() {

}
bool Shade :: end() const {
    return background.getFillColor() == (lighter ? sf :: Color :: Transparent : sf :: Color :: Black);
}
void Shade :: pause() {
    paused = true;
}
void Shade :: run() {
    paused = false;
}
void Shade :: update(const float &deltaTime) {
    if(paused || end()) return;
    const sf :: Color delta(0, 0, 0,  + 0.5f);
    if(lighter) alpha -= 255.f * deltaTime / duration;
    else alpha += 255.f * deltaTime / duration;
    alpha = std :: min(alpha, 255.f), alpha = std :: max(alpha, 0.f);
    background.setFillColor(sf :: Color(0, 0, 0, alpha + 0.5f));
}
void Shade :: render(sf :: RenderTarget* target) {
    background.setSize(sf :: Vector2f (
        static_cast<float>(target -> getSize().x), 
        static_cast<float>(target -> getSize().y)
        )
    );
    target -> draw(background);
}
