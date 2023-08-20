#include <cstdint>
#include <unordered_map>

#include "score.hpp"
#include "brick.hpp"
#include "evevt_tools.hpp"

namespace ar {

std::unordered_map<BricksTypes, uint32_t> score_by_type = {
    {BricksTypes::Stone, 0},
    {BricksTypes::Red, 90},
    {BricksTypes::Green, 80},
    {BricksTypes::Yellow,70},
    {BricksTypes::Purple,70},
    {BricksTypes::Blue, 100},
    {BricksTypes::Orange, 120},
    {BricksTypes::Pink, 60},
    {BricksTypes::BrightBlue, 110},
    {BricksTypes::LiveGift, 100},
    {BricksTypes::SlowGift, 100},
    {BricksTypes::WideGift, 100},
    {BricksTypes::Golden, 300},
    {BricksTypes::Explode, 80}    
};

Score::Score()
    : m_score(0)
{
}

Score::Score(uint32_t score)
    : m_score(score)
{    
}
    
void Score::increase_score(BricksTypes const& type)
{
    m_score += score_by_type[type]; 
}

uint32_t Score::get_score() const
{
    return m_score;
}

} // namespace ar