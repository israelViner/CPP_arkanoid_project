#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "audio_icon.hpp"
#include "texture_settings.hpp"

namespace ar {

AudioIcon::AudioIcon()
    : m_status(false)
    , m_icon({50.f, 50.f})
{
    set_icon_texture();
    m_icon.setPosition(1300, 50);
}

AudioIcon& AudioIcon::get_instance()
{
    static AudioIcon audio;
    return audio;
}

void AudioIcon::set_icon_texture()
{
    std::shared_ptr<TextureSettings> settings = TextureSettings::get_instance();
    
    m_status = !m_status;
    if (m_status) {
        m_icon.setTexture(&(*settings->get_audio_icon()[0]));
        m_icon.setTextureRect(sf::IntRect(0, 0, settings->get_audio_icon()[0]->getSize().x, settings->get_audio_icon()[0]->getSize().y));
    } else {
        m_icon.setTexture(&(*settings->get_audio_icon()[1]));
        m_icon.setTextureRect(sf::IntRect(0, 0, settings->get_audio_icon()[1]->getSize().x, settings->get_audio_icon()[1]->getSize().y));
    }
}

sf::RectangleShape const& AudioIcon::draw() const
{
    return m_icon;
}

} // namespace ar