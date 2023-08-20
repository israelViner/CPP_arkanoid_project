#ifndef AUDIOICON_ICON_H
#define AUDIOICON_ICON_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace ar {

class AudioIcon
{
public:
    AudioIcon(AudioIcon const&) = delete;
    AudioIcon const& operator=(AudioIcon const&) = delete;
    
    static AudioIcon& get_instance();

    void set_icon_texture();
    sf::RectangleShape const& draw() const;

    private:
    AudioIcon();

private:
    bool m_status;
    sf::RectangleShape m_icon; 
};

} // namespace ar

#endif