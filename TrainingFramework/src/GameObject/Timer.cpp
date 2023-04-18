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
	ss2 << std::setw(2) << std::setfill('0') << ((int)gameTimeInSeconds %60);
	std::string s1 = ss1.str();
	std::string s2 = ss2.str();
	return s1 + " : " + s2;
	
}

void Timer::CountSurviveTime(GLfloat deltaTime)
{
	this->gameTimeInMinutes = (gameTimeInMinutes + deltaTime) ;
	this->gameTimeInSeconds = (gameTimeInSeconds + deltaTime) ;
}
void Timer::SetTime(GLfloat timeInMins, GLfloat timeInSecs)
{
	this->gameTimeInMinutes = timeInMins;
	this->gameTimeInSeconds = timeInSecs;
}

GLint Timer::GetTimeInSeconds()
{
	return (int)gameTimeInSeconds % 60;
}

GLint Timer::GetTimeInMinutes()
{
	return (int)this->gameTimeInMinutes/60;
}

