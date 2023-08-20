#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <cassert>
#include <fstream>

#include "texture_settings.hpp"
#include "brick_types_enum.hpp"

namespace ar {

TextureSettings::TextureSettings()
    : m_backround_vector({
        create_texture("assets/background/level01_bg.png"),
        create_texture("assets/background/level02_bg.png"),
        create_texture("assets/background/level03_bg.png"),
        create_texture("assets/background/level04_bg.jpg"),
        create_texture("assets/background/level05_bg.png"),
        create_texture("assets/background/level06_bg.jpg")  
    })
    , m_ball(create_texture("assets/ball/ball.png"))
    , m_paddle(create_texture("assets/paddle/paddle.png"))
    , m_play_button(create_texture("assets/buttons/play.png"))
    , m_quit_button(create_texture("assets/buttons/quit.png"))
    , m_start_crack(create_texture("assets/bricks/break_1.png"))
    , m_crack(create_texture("assets/bricks/break_2.png"))
    , m_audio_icon_vec({
        (create_texture("assets/buttons/unmute.png")),
        (create_texture("assets/buttons/mute.png"))
    })
    , m_brick_textures({
        [](){ sf::Texture stone_brick; stone_brick.loadFromFile("assets/bricks/stone.png"); return std::make_shared<sf::Texture>(stone_brick);},
        [](){ sf::Texture blue_brick; blue_brick.loadFromFile("assets/bricks/blue.png"); return std::make_shared<sf::Texture>(blue_brick);},
        [](){ sf::Texture red_brick; red_brick.loadFromFile("assets/bricks/red.png"); return std::make_shared<sf::Texture>(red_brick);},
        [](){ sf::Texture yellow_brick; yellow_brick.loadFromFile("assets/bricks/gray.png"); return std::make_shared<sf::Texture>(yellow_brick);},
        [](){ sf::Texture pink_brick; pink_brick.loadFromFile("assets/bricks/pink.png"); return std::make_shared<sf::Texture>(pink_brick);},
        [](){ sf::Texture btight_blue_brick; btight_blue_brick.loadFromFile("assets/bricks/light_blue.png"); return std::make_shared<sf::Texture>(btight_blue_brick);},
        [](){ sf::Texture orange_brick; orange_brick.loadFromFile("assets/bricks/orange_brick.png"); return std::make_shared<sf::Texture>(orange_brick);},
        [](){ sf::Texture purple_brick; purple_brick.loadFromFile("assets/bricks/purple.png"); return std::make_shared<sf::Texture>(purple_brick);},
        [](){ sf::Texture green_brick; green_brick.loadFromFile("assets/bricks/green.png"); return std::make_shared<sf::Texture>(green_brick);},
        [](){ sf::Texture live_gift_brick; live_gift_brick.loadFromFile("assets/bricks/life.png"); return std::make_shared<sf::Texture>(live_gift_brick);},
        [](){ sf::Texture slow_gift_brick; slow_gift_brick.loadFromFile("assets/bricks/slow.png"); return std::make_shared<sf::Texture>(slow_gift_brick);},
        [](){ sf::Texture wide_gift_brick; wide_gift_brick.loadFromFile("assets/bricks/wide.png"); return std::make_shared<sf::Texture>(wide_gift_brick);},
        [](){ sf::Texture golden_brick; golden_brick.loadFromFile("assets/bricks/gold.png"); return std::make_shared<sf::Texture>(golden_brick);},
        [](){ sf::Texture explode_brick; explode_brick.loadFromFile("assets/bricks/explode.png"); return std::make_shared<sf::Texture>(explode_brick);}
    })         
    , m_vec_textures({
        {BricksTypes::Stone , m_brick_textures[0]()}, 
        {BricksTypes::Blue ,m_brick_textures[1]()},
        {BricksTypes::Red , m_brick_textures[2]()},
        {BricksTypes::Yellow ,m_brick_textures[3]()},
        {BricksTypes::Pink ,m_brick_textures[4]()},
        {BricksTypes::BrightBlue ,m_brick_textures[5]()},
        {BricksTypes::Orange ,m_brick_textures[2]()},
        {BricksTypes::Purple ,m_brick_textures[7]()},
        {BricksTypes::Green , m_brick_textures[8]()},
        {BricksTypes::LiveGift , m_brick_textures[9]()},
        {BricksTypes::SlowGift , m_brick_textures[10]()},
        {BricksTypes::WideGift , m_brick_textures[11]()},
        {BricksTypes::Golden , m_brick_textures[12]()},
        {BricksTypes::Explode , m_brick_textures[13]()}
    }) 
    , m_sprite_backround(std::make_shared<sf::Sprite>())
{
}

std::shared_ptr<TextureSettings> TextureSettings::get_instance()
{
    static std::shared_ptr<TextureSettings> instance(new TextureSettings);
    return instance; 
}

std::unordered_map<BricksTypes, std::shared_ptr<sf::Texture>>& TextureSettings::get_vec_textures()
{
    return m_vec_textures;
}

std::vector<std::function<std::shared_ptr<sf::Texture>()>>& TextureSettings::get_brick_textures()
{
    return m_brick_textures;
}

std::shared_ptr<sf::Texture>& TextureSettings::get_background(int level)
{
    return m_backround_vector[level - 1];
}

std::shared_ptr<sf::Texture>& TextureSettings::get_texture_ball()
{
    return m_ball;
}

std::shared_ptr<sf::Texture>& TextureSettings::get_texture_paddle()
{
    return m_paddle;
}

std::shared_ptr<sf::Texture>& TextureSettings::get_texture_play()
{
    return m_play_button;
}

std::shared_ptr<sf::Texture>& TextureSettings::get_texture_quit()
{
    return m_quit_button;
}

std::vector<std::shared_ptr<sf::Texture>>& TextureSettings::get_audio_icon()
{
    return m_audio_icon_vec;
}

std::shared_ptr<sf::Texture>& TextureSettings::get_texture_start_crack()
{
    return m_start_crack;
}

std::shared_ptr<sf::Texture>& TextureSettings::get_texture_crack()
{
    return m_crack;
}

std::shared_ptr<sf::Sprite>& TextureSettings::get_sprite_background(sf::RenderWindow const& screen ,int level)
{
    m_sprite_backround->setTexture(*get_background(level));
    float scaleX = static_cast<float>(screen.getSize().x) / get_background(level)->getSize().x;
    float scaleY = static_cast<float>(screen.getSize().y) / get_background(level)->getSize().y;
    m_sprite_backround->setScale(scaleX, scaleY);
    m_sprite_backround->setTextureRect(sf::IntRect(0, 0, screen.getSize().x, screen.getSize().y));  
    return m_sprite_backround;
}

std::shared_ptr<sf::Texture> TextureSettings::create_texture(std::string const& name_file)
{
    sf::Texture texture;
    if (!texture.loadFromFile(name_file)) {
        assert(!"failed to load texture");
    }

    return std::make_shared<sf::Texture>(texture);
}

} // namespace ar
