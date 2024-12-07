#include "Subtitle.h"
Subtitle :: Subtitle(Resource* resource) : resource(resource) {
    this -> text.setString("");
}
Subtitle :: ~Subtitle() {

}

void Subtitle :: setFont(const std :: string &file) {
    this -> text.setFont(*resource -> getFont(file));
}
void Subtitle :: setPosition(const sf :: Vector2f &position) {
    this -> text.setPosition(position);
}
void Subtitle :: display(const std :: wstring &sentence, const float &duration) {
    this -> text.setString(sentence);
    const sf::FloatRect &textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top  + textRect.height / 2.f);
    countdown = duration;
}
void Subtitle :: clear() {
    this -> text.setString("");
    countdown = 0.f;
}
void Subtitle :: update(const float &deltaTime) {
    countdown -= deltaTime;
    if(countdown <= 0.f) this -> clear();
}
void Subtitle :: render(sf :: RenderTarget* target) const {
    if(this -> text.getString() != "") target -> draw(text);
}