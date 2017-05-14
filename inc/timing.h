/* --------------------
	Timing
---------------------*/

#ifndef COMMON_CPP_TIMING_H
#define COMMON_CPP_TIMING_H

#include <chrono>

/* Types */

typedef std::chrono::high_resolution_clock::time_point TP;

enum TimeUnit { HOURS, MINUTES, SECONDS, MILLISECONDS, MICROSECONDS };

/* Functions */

#ifdef COMMON_CPP_HAS_OPENCV
#include <opencv2/core.hpp>
double getTimeNow();
double getDeltaTime(double tickNow, double tickPrev, TimeUnit units = MILLISECONDS);
double getDeltaTime(double tickPrev, TimeUnit units = MILLISECONDS);
double getDeltaTime(int64 tickNow, int64 tickPrev, TimeUnit units = MILLISECONDS);
#endif/*COMMON_CPP_HAS_OPENCV*/

TP getTimeNowPrecise();
double getDeltaTimePrecise(TP now, TP prev, TimeUnit units = MICROSECONDS);
double getDeltaTimePrecise(TP prev, TimeUnit units = MICROSECONDS);

#endif/*COMMON_CPP_TIMING_H*/
