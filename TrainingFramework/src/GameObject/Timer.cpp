#include "Timer.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>



std::string Timer::DisplaySurviveTime()
{
	std::stringstream ss1;
	std::stringstream ss2;
	ss1 << std::setw(2) << std::setfill('0') << ((int)gameTimeInMinutes/60);
	ss2 << std::setw(2) << std::setfill('0') << ((int)gameTimeInMinutes %60);
	std::string s1 = ss1.str();
	std::string s2 = ss2.str();
	return s1 + " : " + s2;
	
}

void Timer::CountSurviveTime(GLfloat deltaTime)
{
	this->gameTimeInMinutes = (gameTimeInMinutes + deltaTime) ;
	this->gameTimeInSeconds = (gameTimeInSeconds + deltaTime) ;
}
void Timer::SetTime()
{
	startTime = std::chrono::steady_clock::now();
}

GLint Timer::GetTime(GLint gameTimeInSeconds, GLint gameTimeInMinutes)
{
	this->gameTimeInSeconds = gameTimeInSeconds;
	this->gameTimeInMinutes = gameTimeInMinutes;
	return gameTimeInSeconds;
}