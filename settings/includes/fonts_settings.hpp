#ifndef FONTS_SETTINGS_H
#define FONTS_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include "brick_types_enum.hpp"

namespace ar {

class FontsSettings
{
public:
    FontsSettings(FontsSettings const&) = delete;
    FontsSettings const& operator=(FontsSettings const&) = delete;

    static FontsSettings& get_instance();

    std::shared_ptr<sf::Font>& get_font_1();  
    std::shared_ptr<sf::Font>& get_font_2();    
  
private:
    FontsSettings();
    std::shared_ptr<sf::Font> create_font(std::string const& name_file);
   
private:
    std::shared_ptr<sf::Font> m_font_1;
    std::shared_ptr<sf::Font> m_font_2;
};

} // namespace ar

#endif