#ifndef TEXTURE_SETTINGS_H
#define TEXTURE_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include "brick_types_enum.hpp"

namespace ar {

class TextureSettings
{
public:
    TextureSettings(TextureSettings const&) = delete;
    TextureSettings const& operator=(TextureSettings const&) = delete;

    static std::shared_ptr<TextureSettings> get_instance();

    std::unordered_map<BricksTypes, std::shared_ptr<sf::Texture>>& get_vec_textures();
    std::vector<std::function<std::shared_ptr<sf::Texture>()>>& get_brick_textures();
    std::shared_ptr<sf::Texture>& get_texture_ball();
    std::shared_ptr<sf::Texture>& get_texture_paddle();
    std::shared_ptr<sf::Texture>& get_texture_play();
    std::shared_ptr<sf::Texture>& get_texture_quit();
    std::vector<std::shared_ptr<sf::Texture>>& get_audio_icon();
    std::shared_ptr<sf::Texture>& get_texture_start_crack();
    std::shared_ptr<sf::Texture>& get_texture_crack();
    std::shared_ptr<sf::Sprite>& get_sprite_background(sf::RenderWindow const& screen ,int level);
  
private:
    TextureSettings();
    std::shared_ptr<sf::Texture> create_texture(std::string const& name_file); 
    std::shared_ptr<sf::Texture>& get_background(int level);

private:
    std::vector<std::shared_ptr<sf::Texture>> m_backround_vector;
    std::shared_ptr<sf::Texture> m_ball;
    std::shared_ptr<sf::Texture> m_paddle;
    std::shared_ptr<sf::Texture> m_play_button;
    std::shared_ptr<sf::Texture> m_quit_button;
    std::shared_ptr<sf::Texture> m_start_crack;
    std::shared_ptr<sf::Texture> m_crack;
    std::vector<std::shared_ptr<sf::Texture>> m_audio_icon_vec;
    std::vector<std::function<std::shared_ptr<sf::Texture>()>> m_brick_textures;
    std::unordered_map<BricksTypes, std::shared_ptr<sf::Texture>> m_vec_textures;
    std::shared_ptr<sf::Sprite> m_sprite_backround;
};

} // namespace ar

#endif