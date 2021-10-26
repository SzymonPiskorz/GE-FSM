#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <SDL_timer.h>


class Clock
{
private: 
    Uint32 m_start;

public:

    Clock();

    void start();
    void restart();

    uint32_t getElapsedTime();
    float getElapsedTimeAsSeconds();
};

#endif 