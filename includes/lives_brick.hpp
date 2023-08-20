#ifndef LIVES_BRICK_H
#define LIVES_BRICK_H

#include <SFML/Graphics.hpp>
#include <cstdint>

namespace ar {

class LivesBrick
{
public:
    explicit LivesBrick(uint8_t lives);
    virtual ~LivesBrick() = default;

    uint8_t get_lives() const;
    void sub_lives();
    bool is_live() const;

private:
    uint8_t m_lives;
};

} // namespace ar

#endif