#include "instruction.h"
#include "position.h"
#include "robot_cleaner.h"
#include <memory>

const int MIN_MOVE_STEP = 1;
const int MAX_MOVE_STEP = 10;

struct SafeguardDecorator;

struct TurnInstruction : Instruction
{
    explicit TurnInstruction(bool _left) { left = _left; }

    bool exec(RobotCleaner &robot) const
    {
        auto pos = robot.getPosition();
        if (pos.turn(left))
        {
            robot.setPosition(pos);
            return true;
        }
        return false;
    }

private:
    bool left;
};

struct MoveInstruction : Instruction
{
    explicit MoveInstruction(bool _forword) { forword = _forword; }

    bool exec(RobotCleaner &robot) const
    {
        auto pos = robot.getPosition();
        if (pos.move(forword))
        {
            robot.setPosition(pos);
            return true;
        }
        return false;
    }

private:
    bool forword;
};

struct RepeatInstruction : Instruction
{
    RepeatInstruction(Instruction *instruction, int times)
        : instruction(instruction), times(times)
    {
    }

    bool exec(RobotCleaner &robot) const
    {
        bool ok = true;
        for (auto i = 0; ok && i < times; ++i)
        {
            ok = instruction->exec(robot);
        }

        return ok;
    }

private:
    std::unique_ptr<Instruction> instruction;
    int times;
};

struct SequentialInstruction : Instruction
{
    explicit SequentialInstruction(
        std::initializer_list<Instruction *> instructions)
        : instructions(instructions)
    {
    }

    bool exec(RobotCleaner &robot) const
    {
        bool ok = true;
        for (auto ins : instructions)
        {
            if (!ok)
            {
                break;
            }
            ok = ins->exec(robot);
        }

        return ok;
    }

    ~SequentialInstruction()
    {
        for (auto ins : instructions)
        {
            delete ins;
        }
    }

private:
    std::initializer_list<Instruction *> instructions;
};

struct ErrorInstruction : Instruction
{
    bool exec(RobotCleaner &robot) const { return true; }
};

#define OUTSIDE_RANG(value)                                                    \
    do                                                                         \
    {                                                                          \
        if (value < MIN_MOVE_STEP || value > MAX_MOVE_STEP)                    \
            return new ErrorInstruction;                                       \
    } while (0)

Instruction *left() { return new TurnInstruction(true); }

Instruction *right() { return new TurnInstruction(false); }

Instruction *repeat(Instruction *instruction, int times)
{
    OUTSIDE_RANG(times);
    return new RepeatInstruction(instruction, times);
}

Instruction *forword(int step);
Instruction *_sequential(std::initializer_list<Instruction *> instructions);

struct SafeguardDecorator : Instruction
{
    explicit SafeguardDecorator(MoveInstruction *instruction)
        : instruction(instruction)
    {
    }

    bool exec(RobotCleaner &robot) const
    {
        if (!instruction->exec(robot))
        {
            robot.exec(_sequential({right(), forword()}));
        }
        return true;
    }

protected:
    std::unique_ptr<MoveInstruction> instruction;
};

Instruction *forword(int step)
{
    OUTSIDE_RANG(step);
    return repeat(new SafeguardDecorator(new MoveInstruction(true)), step);
}

Instruction *backword(int step)
{
    OUTSIDE_RANG(step);
    return repeat(new SafeguardDecorator(new MoveInstruction(false)), step);
}

Instruction *round() { return repeat(right(), 2); }

Instruction *_sequential(std::initializer_list<Instruction *> instructions)
{
    return new SequentialInstruction(instructions);
}
