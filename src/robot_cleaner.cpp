#include "robot_cleaner.h"

using namespace std;

RobotCleaner::RobotCleaner()
    :position(Position(0, 0, NORTH))
{
}

Position RobotCleaner::getPosition() const
{
    return position;
}

void RobotCleaner::exec(Instruction* ins)
{
    ins->exec(position);
    delete ins;
}