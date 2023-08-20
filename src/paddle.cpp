#include <cassert>

#include "paddle.hpp"
#include "texture_settings.hpp"

namespace ar {

Paddle::Paddle(sf::Vector2f const& location)
    : m_paddle(sf::Vector2f(200.f, 30.f))
    , m_wide(false)
{
    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance();
    std::shared_ptr<sf::Texture> paddle_texture = settings->get_texture_paddle();    
    m_paddle.setPosition(location);
    m_paddle.setTexture(&(*paddle_texture));
    m_paddle.setTextureRect(sf::IntRect(0, 0, paddle_texture->getSize().x, paddle_texture->getSize().y));
}

void Paddle::update(sf::Vector2u const& vec)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_paddle.getPosition().x + m_paddle.getSize().x < vec.x) {
        m_paddle.move(sf::Vector2f(2.f, 0.f));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPosition().x > 0) {
        m_paddle.move(sf::Vector2f(-2.f, 0.f));
    }
}

void Paddle::set_wide()
{
    if (!m_wide) {
        sf::Vector2f old_position = m_paddle.getPosition(); 
        float current_width = m_paddle.getSize().x; 
        float new_width = current_width * 2;
        sf::Vector2f new_position(old_position.x - (new_width - current_width) / 2, old_position.y);
        m_paddle.setPosition(new_position);
        m_paddle.setSize(sf::Vector2f(new_width, m_paddle.getSize().y)); 
        m_wide = true;
    }
}

void Paddle::set_thin()
{
    if (m_wide) {
        sf::Vector2f old_position = m_paddle.getPosition(); 
        float current_width = m_paddle.getSize().x; 
        float new_width = current_width / 2;
        sf::Vector2f new_position(old_position.x + new_width / 2, old_position.y);
        m_paddle.setPosition(new_position);
        m_paddle.setSize(sf::Vector2f(new_width, m_paddle.getSize().y));
        m_wide = false;
    } 
}

sf::Vector2f Paddle::getPosition() const
{
    return m_paddle.getPosition();
}

void Paddle::setPosition(sf::Vector2f const& vec)
{
    m_paddle.setPosition(vec);
}

sf::FloatRect Paddle::getGlobalBounds() const
{
    return m_paddle.getGlobalBounds();
}

sf::RectangleShape const& Paddle::get_paddle() const
{
    return m_paddle;
}

sf::Vector2f Paddle::getSize() const
{
    return m_paddle.getSize();
}

} // namespace ar