#include <algorithm>

#include "explosion.hpp"
#include "brick.hpp"
#include "bricks.hpp"
#include "player.hpp"
#include "audio.hpp"

namespace ar {

void explode(Brick& brick, Bricks& bricks, Player& player)
{
    Audio& audio = Audio::get_instance(); 

    sf::FloatRect explode_area =  get_explode_area(brick); 
    std::vector<std::shared_ptr<Brick>> bricks_vec = bricks.get_bricks();
    std::vector<std::shared_ptr<Brick>> intersect_bricks;
        
    auto it = bricks_vec.begin();
    auto end_it = bricks_vec.end();    
    while(it != end_it) {
        if (explode_area.intersects((*it)->getGlobalBounds())) {
            intersect_bricks.push_back(*it); 
        } 
        ++it;    
    }
    while(!intersect_bricks.empty()) {
        auto second_begin = intersect_bricks.begin();
        auto it = std::find_if(bricks_vec.begin(), bricks_vec.end(), [&](std::shared_ptr<Brick> p) { return p == *second_begin; });
        if (*it == *second_begin) {            
            audio.play_brick_hit();                     
            bricks.bricks_destruction(*(*it), player);
        }
        intersect_bricks.erase(second_begin);
    }
}

sf::FloatRect get_explode_area(Brick const& brick)
{
    sf::Vector2f brick_size = brick.getSize();    
    sf::RectangleShape explode_radius({brick_size.x * 5, brick_size.y * 5});
    explode_radius.setOrigin(brick_size.x * 2.5f, brick_size.y * 2.5f);
    float new_x = brick.getPosition().x + brick_size.x / 2;
    float new_y = brick.getPosition().y + brick_size.y / 2;
    explode_radius.setPosition({new_x, new_y});
    sf::FloatRect explode_area = explode_radius.getGlobalBounds();

    return explode_area;
}

} // namespace ar
