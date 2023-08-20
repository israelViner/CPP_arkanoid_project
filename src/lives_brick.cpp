#include <cstdint>

#include "lives_brick.hpp"

namespace ar {

LivesBrick::LivesBrick(uint8_t lives)
    : m_lives(lives)
{    
}
    
void LivesBrick::sub_lives()
{
    if (m_lives > 0) {
        --m_lives;
    }
}

bool LivesBrick::is_live() const
{
    return m_lives;
}

uint8_t LivesBrick::get_lives() const
{
    return m_lives;
}

} // namespace ar