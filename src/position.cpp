#include "position.h"

Position::Position(int x, int y, const Orientation& orientation)
: x(x), y(y), orientation(orientation)
{}

void Position::turn(bool left)
{
	orientation = (Orientation)((orientation + (left ? 3 : 1))%4);
}

static int OFFSETS[4] = {0, 1, 0, -1};

void Position::move(bool forword)
{
	int face = (forword ? 1:-1);
    x = x + OFFSETS[orientation]*face;
    y = y + OFFSETS[(orientation + 1)%4]*face;
}

bool Position::operator ==(const Position &other) const
{
    return x == other.x && y == other.y && orientation == other.orientation;
}
