#include "instruction.h"
#include "position.h"

const int MIN_MOVE_STEP = 1;
const int MAX_MOVE_STEP = 10;

struct TurnInstruction: Instruction
{
	TurnInstruction(bool _left)
    {
		left = _left;
    }

    void exec(Position &pos)
    {
        pos.turn(left);
    }
private:
    bool left;
};

struct MoveInstruction: Instruction
{
	MoveInstruction(bool _forword)
    {
		forword = _forword;
    }

    void exec(Position &pos)
    {
    	pos.move(forword);
    }
private:
    bool forword;
};

struct RepeatInstruction: Instruction
{
	RepeatInstruction(Instruction* instruction, int times)
		: instruction(instruction), times(times)
	{}

	void exec(Position &pos)
	{
		for(int i = 0; i < times; ++i)
		{
			instruction->exec(pos);
		}
	}

	~RepeatInstruction()
	{
		delete instruction;
	}


private:
	Instruction *instruction;
	int times;
};

struct SequentialInstruction: Instruction
{
	SequentialInstruction(std::initializer_list<Instruction*> instructions)
		: instructions(instructions)
	{}

	void exec(Position &pos)
	{
		for(auto ins : instructions)
		{
			ins->exec(pos);
		}
	}

	~SequentialInstruction()
	{
		for(auto ins : instructions)
		{
			delete ins;
		}
	}

private:
	std::initializer_list<Instruction*> instructions;

};

struct ErrorInstruction: Instruction {
	void exec(Position &pos) {}
};

#define OUTSIDE_RANG(value) \
	do {\
		if(value < MIN_MOVE_STEP || value > MAX_MOVE_STEP) \
			return new ErrorInstruction; \
	} while(0)

Instruction *left()
{
	return new TurnInstruction(true);
}

Instruction *right()
{
    return new TurnInstruction(false);
}

Instruction *repeat(Instruction* instruction, int times)
{
	OUTSIDE_RANG(times);
	return new RepeatInstruction(instruction, times);
}

Instruction *forword(int step)
{
	OUTSIDE_RANG(step);
    return repeat(new MoveInstruction(true), step);
}

Instruction *backword(int step)
{
	OUTSIDE_RANG(step);
    return repeat(new MoveInstruction(false), step);
}

Instruction *round()
{
	return repeat(right(), 2);
}

Instruction *_sequential(std::initializer_list<Instruction*> instructions)
{
	return new SequentialInstruction(instructions);
}

