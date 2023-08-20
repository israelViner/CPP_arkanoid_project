#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

#include "lives_brick.hpp"
#include "brick_types_enum.hpp"

namespace ar {

class Brick: public LivesBrick
{
public:
    explicit Brick(sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture);
    ~Brick() = default;

    bool operator==(Brick const& brick);

    virtual BricksTypes get_type() const = 0;
    virtual void update();
    sf::RectangleShape& get_brick();

    virtual void set_texture();
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f const& getSize() const;
    sf::Vector2f const& getPosition() const;
        
private:
    sf::RectangleShape m_brick;
};

} // namespace ar

#endif