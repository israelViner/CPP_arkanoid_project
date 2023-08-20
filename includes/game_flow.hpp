#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

#include "ball.hpp"
#include "bricks.hpp"
#include "player.hpp"
#include "texture_settings.hpp"
#include "fonts_settings.hpp"

namespace ar {

class GameFlow
{
public:
    explicit GameFlow(sf::RenderWindow& screen, Player& player, int level);

    bool run_game(int& level, bool& level_up);
    
    bool update();
    void draw();
    bool freeze(std::string str, size_t txt_size, sf::Keyboard::Key const& keyboard);

private:
    std::shared_ptr<TextureSettings> m_settings;
    FontsSettings& m_fonts_settings;
    sf::RenderWindow& m_screen;
    sf::Vector2u m_limits;
    Player& m_player;
    Ball m_ball;
    Bricks m_bricks;
    sf::Text m_text;
    sf::Sprite& m_bg;
    int m_level;
};

} // namespace ar

#endif