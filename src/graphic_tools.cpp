#ifndef GRAPHIC_TOOLS_H
#define GRAPHIC_TOOLS_H

#include <SFML/Graphics.hpp>

#include "graphic_tools.hpp"

namespace ar {

void center_text(sf::Text& text, sf::Vector2u const& size)
{
    sf::FloatRect bounds = text.getLocalBounds();     
    float centerX = bounds.left + bounds.width / 2.0f;
    float centerY = bounds.top + bounds.height / 2.0f;
    text.setOrigin(centerX, centerY);
    text.setPosition(size.x, size.y);  
}

} // namespace ar

#endif