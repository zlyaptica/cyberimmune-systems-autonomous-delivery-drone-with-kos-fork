#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <time.h>
#include <chrono>
#include <unistd.h>

#include "constants.h"

using namespace std;

class Stopwatch
{
private:
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;
    float elapsedTime = 0;
    bool stopwatchStarted = false;

public:
    Stopwatch();
    void start();
    void restart();
    void stop();
    float getELapsedTime();
    bool isStopwatchStarted();
};

#endif