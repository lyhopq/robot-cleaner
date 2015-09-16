#ifndef POSITION_H
#define POSITION_H

#include "orientation.h"

class Position
{
public:
    Position(int x, int y, const Orientation &);
    bool turn(bool left);
    bool move(bool forword);

    bool operator==(const Position &other) const;

    static void setLimit(int x, int y)
    {
        xlimit = x;
        ylimit = y;
    }

private:
    static int xlimit;
    static int ylimit;

    int x;
    int y;
    Orientation orientation;
};

#endif
