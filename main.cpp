#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "game_flow.hpp"
#include "player.hpp"
#include "opening_screen.hpp"
#include "evevt_tools.hpp"
#include "top_high_score.hpp"
#include "audio.hpp"
#include "texture_settings.hpp"
#include "structure_bricks_settings.hpp"

using namespace ar;

int main()
{
    //StructureBricksSettings::get_instance();

    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance(); 
    Audio& audio = Audio::get_instance();  
    sf::RenderWindow screen(sf::VideoMode(1400, 1000), "SFML window");

    while(screen.isOpen()) {
        int level = 1;
     
        if (!opening_screen(screen)) {
            break;
        }

        Player player({static_cast<float>(screen.getSize().x / 2 - 100), static_cast<float>(screen.getSize().y - 50)}, 3);

        bool level_up;
        while(screen.isOpen() && level <= 6 && player.is_live()) {      
            level_up = true;            
            audio.play_background(level);
            GameFlow game(screen, player, level);            
            
            if(!game.run_game(level, level_up)) {
                audio.close();
                if (!level_up) {
                    break;
                }
            }

            ++level;
            player.set_thin();
            player.increase_lives(1);
        }
        if (level >= 6 || !player.is_live()) {
            diaplay_top_scores(screen, player.get_score());
        }
    }

    return 0;
}