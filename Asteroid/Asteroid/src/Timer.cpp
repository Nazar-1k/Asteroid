#include "Timer.h"

Timer::Timer()
{
    //Initialize the variables
   StartTicks = 0;
   PausedTicks = 0;

   Paused = false;
   Started = false;
}

void Timer::start()
{
    //Start the timer
    Started = true;

    //Unpause the timer
   Paused = false;

    //Get the current clock time
    StartTicks = SDL_GetTicks();
    PausedTicks = 0;
}

void Timer::stop()
{
    //Stop the timer
    Started = false;

    //Unpause the timer
    Paused = false;

    //Clear tick variables
    StartTicks = 0;
    PausedTicks = 0;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if (Started && !Paused)
    {
        //Pause the timer
        Paused = true;

        //Calculate the paused ticks
        PausedTicks = SDL_GetTicks() - StartTicks;
        StartTicks = 0;
    }
}

void Timer::unpause()
{
    //If the timer is running and paused
    if (Started && Paused)
    {
        //Unpause the timer
       Paused = false;

        //Reset the starting ticks
        StartTicks = SDL_GetTicks() - PausedTicks;

        //Reset the paused ticks
        PausedTicks = 0;
    }
}

Uint32 Timer::getTicks() const
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (Started)
    {
        //If the timer is paused
        if (Paused)
        {
            //Return the number of ticks when the timer was paused
            time = PausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - StartTicks;
        }
    }

    return time;
}

bool Timer::isStarted() const
{
    //Timer is running and paused or unpaused
    return Started;
}

bool Timer::isPaused() const
{
    //Timer is running and paused
    return Paused && Started;
}
