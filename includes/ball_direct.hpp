#ifndef BALL_DIRECT_H
#define BALL_DIRECT_H

#include <SFML/Graphics.hpp>

namespace ar {

class BallDirect
{
public:
    BallDirect(BallDirect const&) = delete;
    BallDirect const& operator=(BallDirect const&) = delete;
    
    static BallDirect& get_instance();

    void change_direction(float new_dir); 
    void change_direction(sf::FloatRect& ball_bounds, sf::FloatRect& brick_bounds); 
    void r_direction(bool dir); 
    void set_origin_direction();
    void set_slow();

    sf::Vector2f const& get_direction();

private:
    BallDirect();
    void cancel_slow();

private:
    sf::Vector2f m_origin_direction;
    sf::Vector2f m_direction;
    bool m_is_slow;  
    sf::Clock m_clock; 
};

} // namespace ar

#endif