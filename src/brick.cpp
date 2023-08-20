#include "brick.hpp"

namespace ar {

Brick::Brick(sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture)
    : LivesBrick(lives) 
    , m_brick(size)    
{  
    m_brick.setPosition(location);
    m_brick.setTexture(&(*brick_texture));
    m_brick.setTextureRect(sf::IntRect(0, 0, brick_texture->getSize().x, brick_texture->getSize().y));
}

void Brick::update()
{
    sub_lives();
} 

void Brick::set_texture()
{
}

bool Brick::operator==(Brick const& brick)
{
    return this->getGlobalBounds() == brick.getGlobalBounds();
}

sf::FloatRect Brick::getGlobalBounds() const
{
    return m_brick.getGlobalBounds();
}

sf::Vector2f const& Brick::getSize() const
{
    return m_brick.getSize();
}

sf::Vector2f const& Brick::getPosition() const
{
    return m_brick.getPosition();
}

sf::RectangleShape& Brick::get_brick()
{
    return m_brick;
}

} // namespace ar