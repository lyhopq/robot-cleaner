#include <gtest/gtest.h>
#include "robot_cleaner.h"

class RobotCleanerTest : public testing::Test
{
protected:
    virtual void SetUp()
    {
        robot = new RobotCleaner;
        Position::setLimit(6, 6);
    }
    virtual void TearDown() { delete robot; }

    RobotCleaner *robot;
};

TEST_F(RobotCleanerTest, left_instruction)
{
    robot->exec(left());
    ASSERT_EQ(robot->getPosition(), Position(0, 0, WEST));
}

TEST_F(RobotCleanerTest, double_left_instructions)
{
    robot->exec(left());
    robot->exec(left());
    ASSERT_EQ(robot->getPosition(), Position(0, 0, SOUTH));
}

TEST_F(RobotCleanerTest, right_instruction)
{
    robot->exec(right());
    ASSERT_EQ(robot->getPosition(), Position(0, 0, EAST));
}

TEST_F(RobotCleanerTest, double_right_instructions)
{
    robot->exec(right());
    robot->exec(right());
    ASSERT_EQ(robot->getPosition(), Position(0, 0, SOUTH));
}

TEST_F(RobotCleanerTest, forword_instruction)
{
    robot->exec(forword());
    ASSERT_EQ(robot->getPosition(), Position(0, 1, NORTH));
}

TEST_F(RobotCleanerTest, backword_instruction)
{
    robot->exec(backword());
    ASSERT_EQ(robot->getPosition(), Position(0, -1, NORTH));
}

TEST_F(RobotCleanerTest, left_forword_instruction)
{
    robot->exec(left());
    robot->exec(forword());
    ASSERT_EQ(robot->getPosition(), Position(-1, 0, WEST));
}

TEST_F(RobotCleanerTest, left_backword_instruction)
{
    robot->exec(left());
    robot->exec(backword());
    ASSERT_EQ(robot->getPosition(), Position(1, 0, WEST));
}

TEST_F(RobotCleanerTest, right_forword_instruction)
{
    robot->exec(right());
    robot->exec(forword());
    ASSERT_EQ(robot->getPosition(), Position(1, 0, EAST));
}

TEST_F(RobotCleanerTest, right_backword_instruction)
{
    robot->exec(right());
    robot->exec(backword());
    ASSERT_EQ(robot->getPosition(), Position(-1, 0, EAST));
}

TEST_F(RobotCleanerTest, round_instruction)
{
    robot->exec(round());
    ASSERT_EQ(robot->getPosition(), Position(0, 0, SOUTH));
}

TEST_F(RobotCleanerTest, forword3_instruction)
{
    robot->exec(forword(3));
    ASSERT_EQ(robot->getPosition(), Position(0, 3, NORTH));
}

TEST_F(RobotCleanerTest, backword3_instruction)
{
    robot->exec(backword(3));
    ASSERT_EQ(robot->getPosition(), Position(0, -3, NORTH));
}

TEST_F(RobotCleanerTest, forword0_instruction)
{
    robot->exec(forword(0));
    ASSERT_EQ(robot->getPosition(), Position(0, 0, NORTH));
}

TEST_F(RobotCleanerTest, backword0_instruction)
{
    robot->exec(backword(0));
    ASSERT_EQ(robot->getPosition(), Position(0, 0, NORTH));
}
TEST_F(RobotCleanerTest, forword11_instruction)
{
    robot->exec(forword(11));
    ASSERT_EQ(robot->getPosition(), Position(0, 0, NORTH));
}

TEST_F(RobotCleanerTest, backword11_instruction)
{
    robot->exec(backword(11));
    ASSERT_EQ(robot->getPosition(), Position(0, 0, NORTH));
}

TEST_F(RobotCleanerTest, sequential_instruction)
{
    robot->exec(sequential(left(), forword(), round()));
    ASSERT_EQ(robot->getPosition(), Position(-1, 0, EAST));
}

TEST_F(RobotCleanerTest, sequential_instruction2)
{
    robot->exec(sequential(left(), forword(), right(), backword(), round(),
                           forword(2)));
    ASSERT_EQ(robot->getPosition(), Position(-1, -3, SOUTH));
}
TEST_F(RobotCleanerTest, repeat_instruction)
{
    robot->exec(repeat(left(), 3));
    ASSERT_EQ(robot->getPosition(), Position(0, 0, EAST));
}

TEST_F(RobotCleanerTest, repeat_instruction2)
{
    robot->exec(sequential(right(), forword(), repeat(forword(2), 2)));
    ASSERT_EQ(robot->getPosition(), Position(5, 0, EAST));
}

TEST_F(RobotCleanerTest, enter_safeguard_state)
{
    robot->setPosition(Position(6, 6, NORTH));
    robot->exec(forword());
    ASSERT_EQ(robot->getPosition(), Position(6, 5, SOUTH));
}

TEST_F(RobotCleanerTest, enter_safeguard_state_repeat)
{
    robot->setPosition(Position(6, 6, NORTH));
    robot->exec(forword(3));
    ASSERT_EQ(robot->getPosition(), Position(6, 3, SOUTH));
}

TEST_F(RobotCleanerTest, enter_safeguard_state_sequential)
{
    robot->setPosition(Position(6, 6, NORTH));
    robot->exec(sequential(forword(), left(), forword()));
    ASSERT_EQ(robot->getPosition(), Position(6, 4, SOUTH));
}
