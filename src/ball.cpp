#include <cmath>
#include <cassert>

#include "ball.hpp"
#include "player.hpp"
#include "audio.hpp"
#include "ball_direct.hpp"

namespace ar {

Ball::Ball(sf::Vector2f const& location, sf::Texture& ball_texture)
    : m_direct_ball(BallDirect::get_instance())
    , m_ball(20.f)
{  
    m_ball.setPosition(location);
    m_ball.setTexture(&ball_texture);
    m_ball.setTextureRect(sf::IntRect(0, 0, ball_texture.getSize().x, ball_texture.getSize().y));
}

bool Ball::update(sf::Vector2u const& vec, Player& player)
{
    Audio& audio = Audio::get_instance();
    
    if (getPosition().y + getRadius() * 2 >= vec.y) {
        player.sub_lives(); 
        if(player.is_live()) {
            audio.play_fail();
        }     
        return false;
    }

    if (m_ball.getPosition().x < 0 || m_ball.getPosition().x + m_ball.getPoint(9).x >= vec.x) {
        m_direct_ball.r_direction(false);
    }
    if (m_ball.getPosition().y < 0) {
        m_direct_ball.r_direction(true);        
    }
    
    m_ball.move(m_direct_ball.get_direction());

    return true;
}

void Ball::setPosition(sf::Vector2f const& vec)
{
    m_ball.setPosition(vec);
}

sf::FloatRect Ball::getGlobalBounds() const
{
    return m_ball.getGlobalBounds();
}

sf::Vector2f const& Ball::getPosition() const
{
    return m_ball.getPosition();
}

sf::Vector2f Ball::getPoint(size_t point) const
{
    return m_ball.getPoint(point);
}

size_t Ball::getRadius() const
{
    return m_ball.getRadius();
} 

sf::CircleShape const& Ball::get_ball() const
{
    return m_ball;
}

void Ball::move(sf::Vector2f const& dir)
{
    m_ball.move(m_direct_ball.get_direction());
}

} // namespace ar