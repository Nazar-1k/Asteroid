#pragma once
#include <SDL.h>

//The application time based timer
class Timer
{
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks() const;

	//Checks the status of the timer
	bool isStarted() const;
	bool isPaused() const;

private:
	//The clock time when the timer started
	Uint32 StartTicks;

	//The ticks stored when the timer was paused
	Uint32 PausedTicks;

	//The timer status
	bool Paused;
	bool Started;
};

