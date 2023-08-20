#ifndef TOOLS_H
#define TOOLS_H

#include <SFML/Graphics.hpp>
#include <cstdint>

namespace ar {

bool is_any_key_pressed();

bool is_game_close(sf::RenderWindow& screen);

bool is_pause(sf::RenderWindow& screen, sf::Clock& clock);

} // namespace ar

#endif