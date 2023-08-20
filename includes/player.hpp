#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

#include "score.hpp"
#include "lives_player.hpp"
#include "paddle.hpp"

namespace ar {

class Player: public Paddle, public LivesPlayer, public Score
{
public:
    explicit Player(sf::Vector2f const& location, uint8_t lives); 
};

} // namespace ar

#endif