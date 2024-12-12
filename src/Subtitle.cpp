#include "Subtitle.h"
extern Resource resource;

//Subtitle
Subtitle :: Subtitle() {
    text.setString(L"");
}
Subtitle :: ~Subtitle() {

}
void Subtitle :: setFont(const std :: string &file) {
    text.setFont(*resource.getFont(file));
}
void Subtitle :: setPosition(const sf :: Vector2f &position) {
    text.setPosition(position);
}
void Subtitle :: display(const std :: wstring &sentence, const float &duration) {
    text.setString(sentence);
    const sf::FloatRect &textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    countdown = duration;
}
void Subtitle :: clear() {
    text.setString(L"");
    countdown = 0.f;
}
void Subtitle :: update(const float &deltaTime) {
    countdown -= deltaTime;
    if(countdown <= 0.f) clear();
}
void Subtitle :: render(sf :: RenderTarget* target) const {
    if(text.getString() != L"") target -> draw(text);
}