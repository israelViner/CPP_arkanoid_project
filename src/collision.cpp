#include "collision.hpp"
#include "brick.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "brick_types_enum.hpp"
#include "audio.hpp"
#include "ball_direct.hpp"
#include "explosion.hpp"
#include "bricks.hpp"

namespace ar {

bool paddle_colission(sf::Shape const& a, sf::Shape const& b)
{
    Audio& audio = Audio::get_instance(); 

    sf::FloatRect a_boundingBox = a.getGlobalBounds();
    sf::FloatRect b_boundingBox = b.getGlobalBounds();

    if (a_boundingBox.intersects(b_boundingBox)) {
        audio.play_paddle_hit();
        if (a_boundingBox.top - a_boundingBox.height >= b_boundingBox.top - b_boundingBox.height) {
            return true;
        }     
    }  

    return false;
}

std::vector<std::shared_ptr<Brick>> get_intersects_bricks(sf::FloatRect intersect_area, std::vector<std::shared_ptr<Brick>> const& bricks)
{
    std::vector<std::shared_ptr<Brick>> intersects_bricks;
    for (auto const& brick : bricks) {
        if (intersect_area.intersects(brick->getGlobalBounds())) {
            intersects_bricks.push_back(brick);
        }
    }
    return intersects_bricks;
}

void bricks_collision(Ball& ball, Bricks& bricks, Player& player)
{
    Audio& audio = Audio::get_instance();
    BallDirect& direct_ball = BallDirect::get_instance();
    sf::FloatRect ball_boundingBox = ball.getGlobalBounds();
    
    std::vector<std::shared_ptr<Brick>> bricks_vec = bricks.get_bricks();
    std::vector<std::shared_ptr<Brick>> intersects_bricks = get_intersects_bricks(ball.getGlobalBounds(), bricks_vec);
    
    while (!intersects_bricks.empty()) {
        auto brick = intersects_bricks.begin();
        auto it = std::find(bricks_vec.begin(), bricks_vec.end(), *brick);
        if (it == bricks_vec.end()) {
            break;
        }

        sf::FloatRect brick_boundingBox = (*it)->getGlobalBounds();

        direct_ball.change_direction(ball_boundingBox, brick_boundingBox);
        intersects_bricks.erase(brick);
        if ((*it)->get_type() == BricksTypes::Stone) {
            audio.play_stone();
        } else {
            audio.play_brick_hit();
        } 

        if ((*brick)->get_type() != BricksTypes::Explode) {            
            bricks.bricks_destruction(*(*it), player);
        }else {
            audio.play_explosion();
            explode(*(*it), bricks, player);
        }
        break;
    }
}

} // namespace ar
