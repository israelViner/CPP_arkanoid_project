#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cassert>
#include <functional>

#include "audio.hpp"

namespace ar {

static std::vector<std::function<std::shared_ptr<sf::SoundBuffer>()>> vector_buffers = {
    [](){ sf::SoundBuffer buffer; buffer.loadFromFile("assets/sounds/paddle_hit.ogg"); return std::make_shared<sf::SoundBuffer>(buffer);},
    [](){ sf::SoundBuffer buffer; buffer.loadFromFile("assets/sounds/brick_hit.ogg"); return std::make_shared<sf::SoundBuffer>(buffer);},
    [](){ sf::SoundBuffer buffer; buffer.loadFromFile("assets/sounds/fail.ogg"); return std::make_shared<sf::SoundBuffer>(buffer);},
    [](){ sf::SoundBuffer buffer; buffer.loadFromFile("assets/sounds/game_over.ogg"); return std::make_shared<sf::SoundBuffer>(buffer);},
    [](){ sf::SoundBuffer buffer; buffer.loadFromFile("assets/sounds/explosion.ogg"); return std::make_shared<sf::SoundBuffer>(buffer);},
    [](){ sf::SoundBuffer buffer; buffer.loadFromFile("assets/sounds/stone.ogg"); return std::make_shared<sf::SoundBuffer>(buffer);},
}; 

Audio::Audio()
    : m_is_mute(false)
    , m_backround_vector ({
        [](sf::Music& music){music.openFromFile("assets/sounds/background1.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/background2.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/background3.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/background4.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/background5.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/background6.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/opening_screen.ogg");},
        [](sf::Music& music){music.openFromFile("assets/sounds/opening_screen.ogg");}
    })
    , m_background_music()
    , m_paddle_hit()
    , m_brick_hit()
    , m_buffers({
        vector_buffers[0](),
        vector_buffers[1](),
        vector_buffers[2](),
        vector_buffers[3](),
        vector_buffers[4](),
        vector_buffers[5]()
    })
{
    m_paddle_hit.setBuffer(*m_buffers[0]);
    m_brick_hit.setBuffer(*m_buffers[1]);
    m_fail.setBuffer(*m_buffers[2]);
    m_game_over.setBuffer(*m_buffers[3]);
    m_explosion.setBuffer(*m_buffers[4]);
    m_stone.setBuffer(*m_buffers[5]);
}

Audio& Audio::get_instance()
{
    static Audio audio;
    return audio;
}

void Audio::play_background(int level) 
{ 
    m_backround_vector[level - 1](m_background_music);
    if (!m_is_mute) {
        m_background_music.play();
    }
}

void Audio::play_brick_hit()
{
    if (!m_is_mute) {
        m_brick_hit.play();
    }
}

void Audio::play_game_over()
{
    if (!m_is_mute) {
        m_game_over.play();
    }
}

void Audio::play_explosion()
{
    if (!m_is_mute) {
        m_explosion.play();
    }
}

void Audio::play_fail()
{
    if (!m_is_mute) {
        m_fail.play();
    }
}

void Audio::play_stone()
{
    if (!m_is_mute) {
        m_stone.play();
    }
}

void Audio::close()
{
    m_background_music.stop();
}

void Audio::play_paddle_hit()
{
    if (!m_is_mute) {
        m_paddle_hit.play();
    }
}  

bool Audio::is_mute(sf::Clock& clock)
{    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && clock.getElapsedTime().asSeconds() > 0.2) {
        clock.restart();
        m_is_mute = !m_is_mute;
        mute();
        return true;
    }
    
    return false;
}

void Audio::mute()
{
    if(m_is_mute) {
        m_background_music.pause();
    } else {
        m_background_music.play();
    }
}

} // namespace ar
