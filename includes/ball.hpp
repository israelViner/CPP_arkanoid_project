#ifndef BALL_H
#define BALL_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>

#include "brick.hpp"
#include "player.hpp"
#include "ball_direct.hpp"

namespace ar {

class Ball
{
public:
    explicit Ball(sf::Vector2f const& location, sf::Texture& ball_texture);

    bool update(sf::Vector2u const& vec, Player& player);
    sf::CircleShape const& get_ball() const;

    sf::Vector2f const&  getPosition() const;
    sf::Vector2f getPoint(size_t point) const;
    size_t getRadius() const;  
    void setPosition(sf::Vector2f const& vec);
    sf::FloatRect getGlobalBounds() const; 


    void move(sf::Vector2f const& dir);
    
private:
    BallDirect& m_direct_ball;
    sf::CircleShape m_ball;
};

} // namespace ar

#endif
