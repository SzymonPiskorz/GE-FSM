#ifndef COMMAND_H
#define COMMAND_H

#include "Events.h"
#include <stack>

class Command
{
public:
    virtual ~Command(){};
    virtual void execute(gpp::Events* event) = 0;
private:
    Command(){};
};

class CommandAccendLadder : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT); }
};

class CommandAccendLadderStop : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT); }
};

class CommandAttack : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::ATTACK_START_EVENT); }
};

class CommandAttackStop : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT); }
};

class CommandDecendLadder : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT); }
};

class CommandDecendLadderStop : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT); }
};

class CommandDied : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::DIED_EVENT); }
};

class CommandRevive : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::REVIVED_EVENT); }
};

class CommandRunRight : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT); }
};

class CommandRunRightStop : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT); }
};

class CommandIdle : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::NONE); }
};

class CommandJump : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::JUMP_UP_EVENT); }
};

class CommandThrowAttack : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::THROW_START_EVENT); }
};

class CommandThrowAttackStop : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::THROW_STOP_EVENT); }
};

class CommandSlide : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::SLIDE_EVENT); }
};

class CommandFall : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::FALL_DOWN_EVENT); }
};

class CommandHitGround : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::HIT_GROUND_EVENT); }
};

class CommandLadderBot : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT); }
};

class CommandLadderTop : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT); }
};

class CommandHitWall : public Command
{
public:
    virtual void execute(gpp::Events* event) { event->setCurrent(gpp::Events::Event::HIT_WALL_EVENT); }
};

#endif