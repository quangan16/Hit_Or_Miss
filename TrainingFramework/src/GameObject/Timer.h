#pragma once
#include <chrono>
#include <string>
#include <GLES2/gl2.h>

class Timer
{
private:
    GLfloat gameTimeInMinutes;
    GLfloat gameTimeInSeconds;
    // Get current time
    std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
public:
    Timer::Timer() : gameTimeInMinutes{ 0.f }, gameTimeInSeconds{ 0.f }{}
    std::string DisplaySurviveTime();
    void CountSurviveTime(GLfloat deltaTime);
    void SetTime(GLfloat timeInMins, GLfloat timeInSecs);
    GLint GetTimeInSeconds();
    GLint GetTimeInMinutes();
    // Loop until the program is manually ended
   

    

};

