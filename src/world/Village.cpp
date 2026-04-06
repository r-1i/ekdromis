#include "Village.h"

Village::Village(Hero& hero) : hero_(hero) {}

void Village::render(sf::RenderWindow& window) { hero_.render(window); }
