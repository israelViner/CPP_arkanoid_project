
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <unordered_map>
#include <functional>

#include "ball.hpp"
#include "paddle.hpp"
#include "player.hpp"
#include "gifts.hpp"
#include "ball_direct.hpp"

namespace ar {

std::unordered_map<BricksTypes, GiftType> gift_by_brick = {
    {BricksTypes::NoBrick, GiftType::NoGift},
    {BricksTypes::Stone, GiftType::NoGift},
    {BricksTypes::Red, GiftType::NoGift},
    {BricksTypes::Green, GiftType::NoGift},
    {BricksTypes::Yellow, GiftType::NoGift},
    {BricksTypes::Purple, GiftType::NoGift},
    {BricksTypes::Blue, GiftType::NoGift},
    {BricksTypes::Orange, GiftType::NoGift},
    {BricksTypes::Pink, GiftType::NoGift},
    {BricksTypes::BrightBlue, GiftType::NoGift},
    {BricksTypes::LiveGift, GiftType::Live},
    {BricksTypes::SlowGift, GiftType::Slow},
    {BricksTypes::WideGift, GiftType::Wide},
    {BricksTypes::Golden, GiftType::NoGift}
};

std::unordered_map<GiftType, std::function<void(Player& player)>> choose_gift = {
    {GiftType::Live, live_gift},
    {GiftType::Slow, slow_gift},
    {GiftType::Wide, wide_gift}
};

void execute_gift(Brick& brick, Player& player) {
    BricksTypes type = brick.get_type();
    GiftType gift = gift_by_brick[type];
    if (gift == GiftType::Live || gift == GiftType::Wide || gift == GiftType::Slow) {         
        choose_gift[gift](player);
    } 
}

void live_gift(Player& player)
{
    player.increase_lives(1);
}

void slow_gift(Player& player)
{
    BallDirect& direct_ball = BallDirect::get_instance();
    direct_ball.set_slow();
}

void wide_gift(Player& player)
{
    player.set_wide();
}

} // namespace ar