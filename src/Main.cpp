#include "Game.h"
#include <random>
Resource resource;
Subtitle subtitle;
std :: mt19937 rnd(std :: chrono :: steady_clock :: now().time_since_epoch().count());
int main() {
    Game process;
    process.run();
    return 0;
}