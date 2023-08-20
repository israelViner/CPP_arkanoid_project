#include <cstdint>

#include "lives_player.hpp"

namespace ar {

LivesPlayer::LivesPlayer(uint8_t lives)
    : m_lives(lives)
{    
}
    
void LivesPlayer::sub_lives()
{
    if (m_lives > 0) {
        --m_lives;
    }
}

void LivesPlayer::increase_lives(uint8_t val)
{
    m_lives += val;
}

bool LivesPlayer::is_live() const
{
    return m_lives;
}

uint8_t LivesPlayer::get_lives() const
{
    return m_lives;
}

} // namespace ar