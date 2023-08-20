#ifndef COLISSION_H
#define COLISSION_H

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "ball.hpp"
#include "brick.hpp"
#include "bricks.hpp"
#include "player.hpp"

namespace ar {

bool paddle_colission(sf::Shape const& a, sf::Shape const& b);

void bricks_collision(Ball& ball, Bricks& bricks_vec, Player& player);

std::vector<std::shared_ptr<Brick>> get_intersects_bricks(sf::FloatRect intersect_area, std::vector<std::shared_ptr<Brick>> const& bricks);


} // namespace ar

#endif