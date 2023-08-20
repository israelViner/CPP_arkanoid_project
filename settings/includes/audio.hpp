#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>

namespace ar {

class Audio
{
public:
    Audio(Audio const&) = delete;
    Audio const& operator=(Audio const&) = delete;
    
    static Audio& get_instance();

    void play_background(int level);  
    void play_brick_hit(); 
    void play_paddle_hit(); 
    void play_game_over(); 
    void play_fail();
    void play_explosion();
    void play_stone();
    void close();

    bool is_mute(sf::Clock& clock);

    private:
    Audio();
    void mute();

private:
    bool m_is_mute;
    std::vector<std::function<void(sf::Music&)>> m_backround_vector;
    sf::Music m_background_music;
    sf::Sound m_paddle_hit;
    sf::Sound m_brick_hit;
    sf::Sound m_game_over;
    sf::Sound m_fail;
    sf::Sound m_explosion;
    sf::Sound m_stone;
    std::vector<std::shared_ptr<sf::SoundBuffer>> m_buffers;
};

} // namespace ar

#endif