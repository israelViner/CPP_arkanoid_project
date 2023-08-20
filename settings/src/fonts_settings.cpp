
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <cassert>
#include <fstream>

#include "fonts_settings.hpp"
#include "brick_types_enum.hpp"

namespace ar {

FontsSettings::FontsSettings()
    :m_font_1(create_font("assets/fonts/Gameplay.ttf"))
    , m_font_2(create_font("assets/fonts/MachineGunk-nyqg.ttf"))
{
}

FontsSettings& FontsSettings::get_instance()
{
    static FontsSettings instance;    
    return instance; 
}

std::shared_ptr<sf::Font> FontsSettings::create_font(std::string const& name_file)
{
    sf::Font font;
    if (!font.loadFromFile(name_file))
    {
        assert(!"Wrong file");
    }

    return std::make_shared<sf::Font>(font);
}

std::shared_ptr<sf::Font>& FontsSettings::get_font_1()
{
    return m_font_1;
} 

std::shared_ptr<sf::Font>& FontsSettings::get_font_2()
{
    return m_font_2;
} 

} // namespace ar