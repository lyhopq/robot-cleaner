#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <initializer_list>

class Position;

struct Instruction
{
    virtual bool exec(Position &pos) const = 0;
    virtual ~Instruction() {}
};

Instruction *left();
Instruction *right();
Instruction *forword(int step=1);
Instruction *backword(int step=1);
Instruction *round();

Instruction* _sequential(std::initializer_list<Instruction*>);
#define sequential(...) _sequential({ __VA_ARGS__ })

Instruction *repeat(Instruction*, int);

#endif
