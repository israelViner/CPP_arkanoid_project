#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

#include "bricks.hpp"
#include "brick.hpp"
#include "brick_types_enum.hpp"
#include "brick_classes.hpp"
#include "texture_settings.hpp"
#include "player.hpp"
#include "gifts.hpp"

namespace ar { 

static std::unordered_map<BricksTypes, std::function<std::shared_ptr<Brick>(sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture)>> create_bricks = {
    {BricksTypes::Stone , [](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickStone>(location, size, lives, brick_texture);}},
    {BricksTypes::Blue ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickBlue>(location, size, lives, brick_texture);}},
    {BricksTypes::Red ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickRed>(location, size, lives, brick_texture);}},
    {BricksTypes::Yellow ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickYellow>(location, size, lives, brick_texture);}},
    {BricksTypes::Pink ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickPink>(location, size, lives, brick_texture);}},
    {BricksTypes::BrightBlue ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickBrightBlue>(location, size, lives, brick_texture);}},
    {BricksTypes::Orange ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickOrange>(location, size, lives, brick_texture);}},
    {BricksTypes::Purple ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickPurple>(location, size, lives, brick_texture);}},
    {BricksTypes::Green ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickGreen>(location, size, lives, brick_texture);}},
    {BricksTypes::LiveGift ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickLiveGift>(location, size, lives, brick_texture);}},
    {BricksTypes::SlowGift ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickSlowGift>(location, size, lives, brick_texture);}},
    {BricksTypes::WideGift ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickWideGift>(location, size, lives, brick_texture);}},
    {BricksTypes::Golden ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickGolden>(location, size, lives, brick_texture);}},
    {BricksTypes::Explode ,[](sf::Vector2f const& location, sf::Vector2f const& size, uint8_t lives, std::shared_ptr<sf::Texture>& brick_texture){return std::make_shared<BrickExplode>(location, size, lives, brick_texture);}}
};

Bricks::Bricks(sf::Vector2u const& screen_size, int level)
    : m_num_stones(0)
{
    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance();    
    sf::Vector2f brick_size(120.f, 45.f);

    std::string level_file = "level_structures/level-" + std::to_string(level) + ".dat";
    
    std::ifstream infile(level_file, std::ios::binary);
    if (!infile) {
        assert(!"Wrong file");
    }
    
    uint8_t len_rows;
    infile.read(reinterpret_cast<char*>(&len_rows), sizeof(len_rows));
    uint8_t len_col; 
    infile.read(reinterpret_cast<char*>(&len_col), sizeof(len_col));
    std::vector<std::vector<uint8_t>> bricks_structure;

    uint8_t row_size = 11;
    while (true) {
        if (infile.eof()) {
            break; 
        }        
        std::vector<uint8_t> row_data(row_size);
        infile.read(reinterpret_cast<char*>(row_data.data()), row_size * sizeof(uint8_t));        
        bricks_structure.push_back(row_data);
    }
    infile.close();    

    int y = 20;
    for (size_t i = 0; i < len_rows; ++i) {       
        unsigned int x = 30;             
        for (size_t j = 0; j < len_col; ++j) { 
            if (bricks_structure[i][j]) {      
                if(static_cast<BricksTypes>(bricks_structure[i][j]) == BricksTypes::Stone) {
                    ++m_num_stones;
                }
                
                std::shared_ptr<sf::Texture> texture = settings->get_vec_textures()[static_cast<BricksTypes>(bricks_structure[i][j])]; 
                uint8_t lives = 1;                
                if(static_cast<BricksTypes>(bricks_structure[i][j]) == BricksTypes::Golden) {
                    lives = 3;
                }
                std::shared_ptr<Brick> new_brick = create_bricks[static_cast<BricksTypes>(bricks_structure[i][j])](sf::Vector2f(x, y), brick_size, lives, texture);
                m_vec_brick.push_back(new_brick);
            }
            x += brick_size.x;
        }
        y += brick_size.y;
    }
}

std::vector<std::shared_ptr<Brick>> const& Bricks::get_bricks()
{
    return m_vec_brick;
}

bool Bricks::is_empty() const
{
    if (m_vec_brick.size() == m_num_stones) {
        return true;
    }

    return false;
}

void Bricks::bricks_destruction(Brick& brick, Player& player)
{
    execute_gift(brick, player);
    if (brick.get_type() != BricksTypes::Stone) {
        brick.update();
        if (!brick.is_live()) {        
            player.increase_score(brick.get_type());
            auto it = m_vec_brick.begin();
            auto end_it = m_vec_brick.end();
            while (it != end_it) {        
                if (*(*it) == brick) {
                    m_vec_brick.erase(it);
                    break;
                }
                ++it;
            }     
        }
    }
}

} // namespace ar
