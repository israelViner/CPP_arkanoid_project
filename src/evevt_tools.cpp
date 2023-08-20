#include <SFML/Graphics.hpp>
#include <memory>

#include "evevt_tools.hpp"
#include "graphic_tools.hpp"
#include "fonts_settings.hpp"

namespace ar
{

bool is_any_key_pressed()
{
    for (int key = 0; key < sf::Keyboard::KeyCount; ++key) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
            return true;
        }
    }
    return false;
}

bool is_game_close(sf::RenderWindow &screen)
{
    sf::Event event;
    while (screen.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            screen.close();
            return true;
        }
    }

    return false;
}

bool is_pause(sf::RenderWindow &screen, sf::Clock& clock)
{   
    FontsSettings& fonts_settings = FontsSettings::get_instance();
    std::shared_ptr<sf::Font> font = fonts_settings.get_font_2();
    sf::Text text("Pause", *font, 100);
    center_text(text, sf::Vector2u(screen.getSize().x / 2, screen.getSize().y / 2));
    sf::Text text1("press P to resume", *font, 50);
    center_text(text1, sf::Vector2u(screen.getSize().x / 2, (screen.getSize().y / 2) + 80));
        
    sf::Event event;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && clock.getElapsedTime().asSeconds() > 0.2) {
        clock.restart();
        while (true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && clock.getElapsedTime().asSeconds() > 0.2) {
                clock.restart();
                return true;
            }
            while (screen.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    screen.close();
                    return false;
                }
            }
            screen.draw(text);
            screen.draw(text1);
            screen.display();
        }
    }
    return true;
}

} // namespace ar