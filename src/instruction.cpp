#include "instruction.h"
#include "position.h"
#include <memory>

const int MIN_MOVE_STEP = 1;
const int MAX_MOVE_STEP = 10;

struct SafeguardDecorator;

struct TurnInstruction: Instruction
{
	TurnInstruction(bool _left)
    {
		left = _left;
    }

    bool exec(Position &pos) const
    {
        return pos.turn(left);
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

    bool exec(Position &pos) const
    {
    	return pos.move(forword);
    }
private:
    bool forword;
};

struct RepeatInstruction: Instruction
{
	RepeatInstruction(Instruction* instruction, int times)
		: instruction(instruction), times(times)
	{}

    bool exec(Position &pos) const
	{
		bool ok = true;
		for(int i = 0; ok && i < times; ++i)
		{
			ok = instruction->exec(pos);
		}

		return ok;
	}

private:
	std::unique_ptr<Instruction> instruction;
	int times;
};

struct SequentialInstruction: Instruction
{
	SequentialInstruction(std::initializer_list<Instruction*> instructions)
		: instructions(instructions)
	{}

    bool exec(Position &pos) const
	{
		bool ok = true;
		for(auto ins : instructions)
		{
			if(!ok)
			{
				break;
			}
			ok = ins->exec(pos);
		}

		return ok;
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
	bool exec(Position &pos) const {return true;}
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

Instruction *forword(int step);

struct SafeguardDecorator:Instruction
{
	SafeguardDecorator(MoveInstruction *instruction)
		:instruction(instruction)
	{}

    bool exec(Position &pos) const
	{
		if(!instruction->exec(pos))
		{
			right()->exec(pos);
			return forword()->exec(pos);
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

Instruction *round()
{
	return repeat(right(), 2);
}

Instruction *_sequential(std::initializer_list<Instruction*> instructions)
{
	return new SequentialInstruction(instructions);
}
