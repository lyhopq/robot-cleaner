#ifndef ROBOT_H
#define ROBOT_H

#include "position.h"
#include "instruction.h"

class RobotCleaner
{
public:
    RobotCleaner();

    Position getPosition() const;
    void setPosition(Position pos);

    void exec(Instruction *ins);

private:
    Position position;
};

#endif
