#include <Clock.h>

Clock::Clock()
{
    restart();
}

void Clock::start()
{
    m_start = SDL_GetTicks();
}

void Clock::restart()
{
    m_start = 0;
    start();
}

uint32_t Clock::getElapsedTime()
{
    return SDL_GetTicks() - m_start;
}

float Clock::getElapsedTimeAsSeconds()
{
    return getElapsedTime() / 1000.0f;
}