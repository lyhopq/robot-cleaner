#ifndef POSITION_H
#define POSITION_H

#include "orientation.h"

class Position
{
public:
    Position(int x, int y, const Orientation&);
    void turn(bool left);
    void move(bool forword);
    
    bool operator ==(const Position &other) const;

private:
    int x;
    int y;
    Orientation orientation;
};


#endif
