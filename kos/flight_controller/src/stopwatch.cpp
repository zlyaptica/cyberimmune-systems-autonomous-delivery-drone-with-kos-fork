#include "../include/stopwatch.h"

Stopwatch::Stopwatch()
{
}
void Stopwatch::start()
{
    startTime = chrono::high_resolution_clock::now();
}

void Stopwatch::restart()
{
    elapsedTime = 0;
}

void Stopwatch::stop()
{
}

float Stopwatch::getELapsedTime()
{
    endTime = chrono::high_resolution_clock::now();
    auto duration = ::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    elapsedTime += duration.count() / 1e9;
    return elapsedTime;
}

bool Stopwatch::isStopwatchStarted()
{
    return stopwatchStarted;
}
