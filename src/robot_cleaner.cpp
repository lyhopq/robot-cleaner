#include "robot_cleaner.h"

RobotCleaner::RobotCleaner() : position(Position(0, 0, NORTH)) {}

Position RobotCleaner::getPosition() const { return position; }

void RobotCleaner::exec(Instruction *ins)
{
    ins->exec(*this);
    delete ins;
}

void RobotCleaner::setPosition(Position pos) { position = pos; }
