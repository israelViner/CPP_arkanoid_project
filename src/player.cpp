#include <cstdint>

#include "player.hpp"

namespace ar {

Player::Player(sf::Vector2f const& location, uint8_t lives)
    : Paddle(location)
    , LivesPlayer(lives)
    , Score()
{
}

} // namespace ar