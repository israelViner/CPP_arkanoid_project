#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>

#include "game_flow.hpp"
#include "ball.hpp"
#include "bricks.hpp"
#include "collision.hpp"
#include "player.hpp"
#include "top_high_score.hpp"
#include "opening_screen.hpp"
#include "evevt_tools.hpp"
#include "graphic_tools.hpp"
#include "audio_icon.hpp"
#include "audio.hpp"
#include "ball_direct.hpp"
#include "fonts_settings.hpp"
#include "texture_settings.hpp"

namespace ar {

GameFlow::GameFlow(sf::RenderWindow& screen, Player &player, int level)
    : m_settings(TextureSettings::get_instance())
    , m_fonts_settings(FontsSettings::get_instance())
    , m_screen(screen)
    , m_limits(screen.getSize())
    , m_player(player)
    , m_ball({m_player.getPosition().x + 74, m_player.getPosition().y - 43}, *(m_settings->get_texture_ball()))
    , m_bricks(m_limits, level)
    , m_text("Score: " + std::to_string(m_player.get_score()) + "\nLives: " + std::to_string(m_player.get_lives()) + "\nlevel: " + std::to_string(level), *(m_fonts_settings.get_font_1()), 40)
    , m_bg(*(m_settings->get_sprite_background(screen, level)))
    , m_level(level)
{
    m_text.setPosition(sf::Vector2f(0.f, 0.f));
}

bool GameFlow::freeze(std::string str, size_t txt_size, sf::Keyboard::Key const &keyboard)
{
    sf::Clock clock;
    Audio& audio = Audio::get_instance();
    AudioIcon& audio_icon = AudioIcon::get_instance();

    BallDirect& direct_ball = BallDirect::get_instance();

    std::shared_ptr<sf::Font> font = m_fonts_settings.get_font_2();
    sf::Text text(str, *font, txt_size);
    center_text(text, sf::Vector2u(m_screen.getSize().x / 2, m_screen.getSize().y / 2));

    while (m_screen.isOpen()) {

        while (!sf::Keyboard::isKeyPressed(keyboard) || clock.getElapsedTime().asSeconds() < 0.2) {
            if(is_game_close(m_screen)) {
                return false;
            }
            if (audio.is_mute(clock)) {
                audio_icon.set_icon_texture();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                return false;
            }            
            m_player.update(m_screen.getSize());
            m_ball.setPosition({m_player.getPosition().x + 74, m_player.getPosition().y - 43});
            direct_ball.set_origin_direction();
            draw();
            m_screen.draw(text);
            m_screen.draw(audio_icon.draw());
            m_screen.display();
        }
        break;
    }

    return true;
}

void GameFlow::draw()
{
    m_screen.clear(sf::Color(0, 0, 102));
    m_screen.draw(m_bg);
    m_screen.draw(m_ball.get_ball());
    m_screen.draw(m_player.get_paddle());
    std::vector<std::shared_ptr<Brick>> bricks_vec = m_bricks.get_bricks();
    auto it = bricks_vec.begin();
    auto end_it = bricks_vec.end();
    while (it != end_it)  {
        m_screen.draw((*it)->get_brick());
        ++it;
    }
    m_screen.draw(m_text);
}

bool GameFlow::update()
{
    bool res = true;
    Audio& audio = Audio::get_instance();

    BallDirect& direct_ball = BallDirect::get_instance();
    
    bricks_collision(m_ball, m_bricks, m_player);
    m_player.update(m_screen.getSize());
    if (!m_ball.update(m_screen.getSize(), m_player) && m_player.is_live()) {
        m_player.set_thin();
        m_player.setPosition({static_cast<float>(m_limits.x / 2 - 100), static_cast<float>(m_limits.y - 50)});
        m_ball.setPosition({m_player.getPosition().x + 74, m_player.getPosition().y - 43});
        direct_ball.set_origin_direction();
        res = freeze("You can try again!\n\t\t(press Up)", 100, sf::Keyboard::Up);
    }
    if (!m_player.is_live()) {
        audio.play_game_over();
        res = freeze("Game over!", 150, sf::Keyboard::Space);
        return false;
    }
    
    if (m_bricks.is_empty()) {        
        m_player.set_thin();
        res = freeze("Well done!\nscore: " + std::to_string(m_player.get_score()), 100, sf::Keyboard::Space);
        return false;
    }

    if (paddle_colission(m_player.get_paddle(), m_ball.get_ball())) {
        float new_dir = ((m_ball.getPosition().x + m_ball.getRadius()) - (m_player.getPosition().x + m_player.getSize().x / 2)) / (m_player.getSize().x / 2);
        direct_ball.change_direction(new_dir);
    }

    m_text.setString("Score: " + std::to_string(m_player.get_score()) + "\nLives: " + std::to_string(m_player.get_lives()) + + "\nLevel: " + std::to_string(m_level));
    m_text.setPosition(sf::Vector2f(10.f, 10.f));

    return res;
}

bool GameFlow::run_game(int& level, bool& level_up)
{
    sf::Clock clock;
    Audio& audio = Audio::get_instance();
    AudioIcon& audio_icon = AudioIcon::get_instance();

    freeze("\tTo start \n\tpress Up", 100, sf::Keyboard::Up);

    while (m_screen.isOpen()) { 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            return true;
        }         
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && clock.getElapsedTime().asSeconds() > 0.2) {
            level_up = false;
            return false;
        } 
        if(!is_pause(m_screen, clock)) {
            return false;
        }  
        if(is_game_close(m_screen)) {
            return false;
        }
        if (audio.is_mute(clock)) {
            audio_icon.set_icon_texture();
        }    
        if (!update()) {
            if(!m_player.is_live()) {
                level_up = false;
            }            
            return false;
        }
        draw();
        m_screen.draw(audio_icon.draw());
        m_screen.display();         
    }
    return true;
}

} // namespace ar
