#include "position.h"
#include <cmath>

int Position::xlimit = 0;
int Position::ylimit = 0;

Position::Position(int x, int y, const Orientation& orientation)
	: x(x), y(y), orientation(orientation)
{}

bool Position::turn(bool left)
{
	orientation = (Orientation)((orientation + (left ? 3 : 1))%4);
	return true;
}

static int OFFSETS[4] = {0, 1, 0, -1};

bool Position::move(bool forword)
{
	int face = (forword ? 1:-1);
    int x_ = x + OFFSETS[orientation]*face;
    int y_ = y + OFFSETS[(orientation + 1)%4]*face;
    if(abs(x_) > xlimit || abs(y_) > ylimit)
    {
    	return false;
    }
    x = x_;
    y = y_;
    return true;
}

bool Position::operator ==(const Position &other) const
{
    return x == other.x && y == other.y && orientation == other.orientation;
}
