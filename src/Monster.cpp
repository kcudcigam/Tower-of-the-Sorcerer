#include "Monster.h"
//Monster
Monster :: Monster(const std :: wstring &name) : name(name), cnt({0, 0}) {

}
Monster :: ~Monster() {

}
bool Monster :: any() const {
    return cnt.second > 0;
}
const std :: wstring& Monster :: getName() const {
    return name;
}
Attribute& Monster :: getAttribute() {
    return attribute;
}
AnimationSet& Monster :: getAnimation() {
    return animation;
}
void Monster :: insertAction(const std :: string &key, const Animation &action) {
    animation.insert(key, action);
}
void Monster :: setAttribute(const std :: string &key, const int &value) {
    attribute.set(key, value);
    if(key == "health") attribute.set("max_health", value);
}
void Monster :: add() {
    cnt.first++, cnt.second++;
}
void Monster :: del() {
    assert(cnt.first > 0); cnt.first--;
}