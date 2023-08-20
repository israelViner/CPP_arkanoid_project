#include <SFML/Graphics.hpp>
#include <cmath>

#include "ball_direct.hpp"

namespace ar {

BallDirect::BallDirect()
    : m_origin_direction(sf::Vector2f(-0.707f, -0.707f)) 
    , m_direction(m_origin_direction)
    , m_is_slow(false)
    , m_clock() 
{
}

BallDirect& BallDirect::get_instance()
{
    static BallDirect direct_ball;
    return direct_ball;
}

sf::Vector2f const& BallDirect::get_direction()
{
    if (m_is_slow && m_clock.getElapsedTime().asSeconds() > 20) {
        cancel_slow();
    }
    return m_direction;
}

void BallDirect::change_direction(float new_dir)
{
    float norma = 1;
    if (m_is_slow) {
        norma = 2;
    }

    float normal = norma * sqrt(pow(new_dir, 2) + pow(m_direction.y, 2));
    
    m_direction.x = new_dir / normal;
    m_direction.y = (- m_direction.y) / normal;
    m_direction.y -= 0.2;
} 

void BallDirect::change_direction(sf::FloatRect& ball_bounds, sf::FloatRect& brick_bounds)
{
    if (ball_bounds.top < brick_bounds.top || ball_bounds.top + ball_bounds.height < brick_bounds.top || ball_bounds.top + ball_bounds.height > brick_bounds.top  + brick_bounds.height)
    {
        r_direction(true);                            
    } else if (ball_bounds.left < brick_bounds.left || ball_bounds.left + ball_bounds.width < brick_bounds.left || ball_bounds.left + ball_bounds.width > brick_bounds.left + brick_bounds.width) {
        r_direction(false);
    }
} 

void BallDirect::r_direction(bool dir)
{
    if (dir) {
        m_direction.y *= -1;
    } else {
        m_direction.x *= -1;
    } 
} 

void BallDirect::set_origin_direction()
{
    m_direction = m_origin_direction;
}

void BallDirect::set_slow()
{
    if (!m_is_slow) {
        m_direction.x /= 2;
        m_direction.y /= 2;
        m_is_slow = true;
    }
    m_clock.restart();
}

void BallDirect::cancel_slow()
{    
    m_direction.x *= 2;
    m_direction.y *= 2;
    m_is_slow = false;    
}

} // namespace ar