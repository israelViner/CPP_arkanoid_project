#ifndef BRICK_CLASSES_H
#define BRICK_CLASSES_H

#include "brick_types_enum.hpp"
#include "brick.hpp"

namespace ar {

class BrickStone: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickRed: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickGreen: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickYellow: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickPurple: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickBlue: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickOrange: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickPink: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickBrightBlue: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickLiveGift: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickSlowGift: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickWideGift: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickExplode: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
};

class BrickGolden: public Brick
{
public:
    using Brick::Brick;

    BricksTypes get_type() const override;
        
    void update() override;
    void set_texture() override;
};

} // namespace ar

#endif