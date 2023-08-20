#include <SFML/Graphics.hpp>
#include <cassert>

#include "opening_screen.hpp"
#include "evevt_tools.hpp"
#include "audio.hpp"
#include "audio_icon.hpp"
#include "fonts_settings.hpp"
#include "texture_settings.hpp"

namespace ar {

bool opening_screen(sf::RenderWindow& screen)
{
    sf::Clock clock;
    Audio& audio = Audio::get_instance();
    audio.play_background(7);
    AudioIcon& audio_icon = AudioIcon::get_instance();              

    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance();
    std::shared_ptr<sf::Sprite> background = settings->get_sprite_background(screen, 4);
    FontsSettings& fonts_settings = FontsSettings::get_instance();
    std::shared_ptr<sf::Font> font = fonts_settings.get_font_2(); 

    sf::Text text("Welcome to the game", *font, 80);
    text.setPosition(sf::Vector2f(screen.getSize().x / 4, screen.getSize().y * 3/10));

    std::shared_ptr<sf::Texture> play_texture = settings->get_texture_play();    
    sf::RectangleShape play_button(sf::Vector2f(350.f, 100.f));
    play_button.setPosition({static_cast<float>(screen.getSize().x * 5.2/10), static_cast<float>(screen.getSize().y * 5/10)});
    play_button.setTexture(&(*play_texture));
    play_button.setTextureRect(sf::IntRect(0, 0, play_texture->getSize().x, play_texture->getSize().y));

    std::shared_ptr<sf::Texture> quit_texture = settings->get_texture_quit();  
    sf::RectangleShape quit_button(sf::Vector2f(350.f, 100.f));
    quit_button.setPosition({static_cast<float>(screen.getSize().x * 2.4/10), static_cast<float>(screen.getSize().y * 5/10)});
    quit_button.setTexture(&(*quit_texture));
    quit_button.setTextureRect(sf::IntRect(0, 0, quit_texture->getSize().x, quit_texture->getSize().y));
    
    while (screen.isOpen()) {       
        screen.clear();        
       
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(screen);
        sf::FloatRect play_pos = play_button.getGlobalBounds();
        sf::FloatRect quit_pos = quit_button.getGlobalBounds();        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && play_pos.contains(mouse_pos.x, mouse_pos.y))
        {
            return true;
        }  
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && quit_pos.contains(mouse_pos.x, mouse_pos.y))
        {
            return false;
        }        
        if(is_game_close(screen)) {
            return false;
        }                
        if (audio.is_mute(clock)) {
            audio_icon.set_icon_texture();
        }      

        screen.draw(*background);      
        screen.draw(audio_icon.draw());
        screen.draw(play_button);
        screen.draw(quit_button);
        screen.draw(text);
        screen.display();
    }

    return true;
}

} // namespace ar