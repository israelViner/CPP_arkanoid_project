#include "brick_classes.hpp"
#include "brick_types_enum.hpp"
#include "texture_settings.hpp"

namespace ar {

BricksTypes BrickBlue::get_type() const 
{
    return BricksTypes::Blue;
}

BricksTypes BrickStone::get_type() const 
{
    return BricksTypes::Stone;
}

BricksTypes BrickRed::get_type() const 
{
    return BricksTypes::Red;
}

BricksTypes BrickGreen::get_type() const 
{
    return BricksTypes::Green;
}

BricksTypes BrickYellow::get_type() const 
{
    return BricksTypes::Golden;
}

BricksTypes BrickPurple::get_type() const 
{
    return BricksTypes::Purple;
}

BricksTypes BrickOrange::get_type() const 
{
    return BricksTypes::Orange;
}

BricksTypes BrickPink::get_type() const 
{
    return BricksTypes::Pink;
}

BricksTypes BrickBrightBlue::get_type() const 
{
    return BricksTypes::BrightBlue;
}

BricksTypes BrickLiveGift::get_type() const 
{
    return BricksTypes::LiveGift;
}

BricksTypes BrickSlowGift::get_type() const 
{
    return BricksTypes::SlowGift;
}

BricksTypes BrickWideGift::get_type() const 
{
    return BricksTypes::WideGift;
}

BricksTypes BrickExplode::get_type() const 
{
    return BricksTypes::Explode;
}

BricksTypes BrickGolden::get_type() const 
{
    return BricksTypes::Golden;
}

void BrickGolden::update() 
{
    sub_lives();
    if (get_lives() >= 1) {
        set_texture();
    }
}

void BrickGolden::set_texture()
{
    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance(); 
    
    std::shared_ptr<sf::Texture> texture;    
    if (get_lives() == 2) {
        texture = settings->get_texture_start_crack();
    } else if (get_lives() == 1) {
        texture = settings->get_texture_crack();
    }

    get_brick().setTexture(&(*texture));
    get_brick().setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
}

} // namespace ar