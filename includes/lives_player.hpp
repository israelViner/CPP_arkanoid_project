#ifndef LIVES_PLAYER_H
#define LIVES_PLAYER_H

#include <SFML/Graphics.hpp>
#include <cstdint>

namespace ar {

class LivesPlayer
{
public:
    explicit LivesPlayer(uint8_t lives);
    virtual ~LivesPlayer() = default;

    uint8_t get_lives() const;
    void sub_lives();
    bool is_live() const;
    void increase_lives(uint8_t val);

private:
    uint8_t m_lives;
};

} // namespace ar

#endif