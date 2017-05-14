#include "timing.h"

#ifdef COMMON_CPP_HAS_OPENCV
double getTimeNow()
{
    return (double)cv::getTickCount();
}

double getDeltaTime(double tickNow, double tickPrev, TimeUnit units)
{
    double mult = (units == HOURS)        ? 1.0 / 3600.0 :
                  (units == MINUTES)      ? 1.0 / 60.0 :
                  (units == SECONDS)      ? 1.0 :
                  (units == MILLISECONDS) ? 1000.0 :
                  (units == MICROSECONDS) ? 1000000.0 : -1;
    return (tickNow - tickPrev) / cv::getTickFrequency() * mult;
}

double getDeltaTime(double tickPrev, TimeUnit units)
{
    return getDeltaTime(getTimeNow(), tickPrev, units);
}

double getDeltaTime(int64 tickNow, int64 tickPrev, TimeUnit units)
{
    return getDeltaTime((double)tickNow, (double)tickPrev, units);
}
#endif/*COMMON_CPP_HAS_OPENCV*/

TP getTimeNowPrecise()
{
    return std::chrono::high_resolution_clock::now();
}

double getDeltaTimePrecise(TP now, TP prev, TimeUnit units)
{
    if (units == MICROSECONDS)
        return std::chrono::duration<double, std::micro>(now - prev).count();
    else if (units == MILLISECONDS)
        return std::chrono::duration<double, std::milli>(now - prev).count();
    else if (units == SECONDS)
        return std::chrono::duration<double>(now - prev).count();
    else if (units == MINUTES)
        return std::chrono::duration<double, std::ratio<60, 1>>(now - prev).count();
    else if (units == HOURS)
        return std::chrono::duration<double, std::ratio<3600, 1>>(now - prev).count();
    return -1;
}

double getDeltaTimePrecise(TP prev, TimeUnit units)
{
    return getDeltaTimePrecise(getTimeNowPrecise(), prev, units);
}
