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
    Timer::Timer() : gameTimeInMinutes{ 0 }, gameTimeInSeconds{ 0 }{};
    std::string DisplaySurviveTime();
    void CountSurviveTime(GLfloat deltaTime);
    void SetTime();
    GLint GetTime(GLint gameTimeInSeconds, GLint gameTimeInMinutes);
    // Loop until the program is manually ended
   

    

};

