#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>

#include "brick.hpp"
#include "bricks.hpp"
#include "player.hpp"

namespace ar {

void explode(Brick& brick, Bricks& bricks, Player& player);

sf::FloatRect get_explode_area(Brick const& brick);

} // namespace ar

#endif