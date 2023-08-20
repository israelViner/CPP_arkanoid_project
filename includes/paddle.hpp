#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

namespace ar {

class Paddle
{
public:
    explicit Paddle(sf::Vector2f const &location);
    virtual ~Paddle() = default;

    void update(sf::Vector2u const& vec);
    sf::RectangleShape const& get_paddle() const;

    void set_wide();
    void set_thin();     
    void setPosition(sf::Vector2f const& vec);
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

private:
    sf::RectangleShape m_paddle;
    bool m_wide;
};

} // namespace ar

#endif