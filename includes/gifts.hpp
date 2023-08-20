#ifndef GIFTS_H
#define GIFTS_H

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "ball.hpp"
#include "paddle.hpp"
#include "player.hpp"
#include "brick.hpp"

namespace ar
{

enum class GiftType : int8_t
{
    NoGift,
    Live,
    Slow,
    Wide
};

void live_gift(Player &player);
void slow_gift(Player &player);
void wide_gift(Player &player);

void execute_gift(Brick &brick, Player &player);

} // namespace ar

#endif