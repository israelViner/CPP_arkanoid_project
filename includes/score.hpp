#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <unordered_map>

#include "brick.hpp"
#include "evevt_tools.hpp"

namespace ar {

class Score
{
public:
    Score();
    explicit Score(uint32_t score);
    virtual ~Score() = default;
    
    void increase_score(BricksTypes const& type);
    uint32_t get_score() const;

private:
    uint32_t m_score;
};

} // namespace ar

#endif