#ifndef BRICKS_H
#define BRICKS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "brick.hpp"
#include "player.hpp"

namespace ar {

class Bricks
{
public:
    Bricks(sf::Vector2u const& vec, int level);
    
    std::vector<std::shared_ptr<Brick>> const& get_bricks();
    bool is_empty() const;

    void bricks_destruction(Brick& brick, Player& player);
    
private:

private:
    std::vector<std::shared_ptr<Brick>> m_vec_brick;
    unsigned int m_num_stones;
};

} // namespace ar

#endif