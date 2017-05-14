/* Testing Utilities */

#ifndef COMMON_CPP_TESTING_H
#define COMMON_CPP_TESTING_H

#include "logging.h"

#include <algorithm>
#include <limits>
#include <sstream>
#include <fstream>

/* --------------------
Types
---------------------*/

enum TestStatus  // errors should be defined as negative values (-#) to ensure 'RETURN_ERROR' functionality
{
	PASSED		= 0,
    SKIPPED     = 1,
    OBSOLETE    = 2
};

/* --------------------
Display
---------------------*/

int passThroughDisplayTestStatus(std::string testName, int error = TestStatus::PASSED);

/* --------------------
Paths
---------------------*/

bool checkPathEndSlash(std::string path);

/* --------------------
Compare
---------------------*/

inline bool doubleAlmostEquals(double x1, double x2, double eps = std::numeric_limits<double>::epsilon())
{
    return std::abs(x1 - x2) < std::abs(std::min(x1, x2)) * eps;
}

/* --------------------
Asserts / Return Macros
---------------------*/

// Throw the given message
#define THROW(msg)										\
do {													\
	std::ostringstream oss;								\
	oss << msg;											\
	throw std::runtime_error(oss.str());				\
} while(0)

// Assert with message printing
#define ASSERT_THROW(cond, msg)                         \
do {                                                    \
    if (!(cond)) {                                      \
    std::ostringstream oss;                             \
    oss << msg;                                         \
    std::string str = "Assertion failed: " + oss.str(); \
    THROW(str); }										\
} while(0)

// Assert with message printing
#define ASSERT_MSG(cond, msg)                           \
do {                                                    \
    if (!(cond)) {                                      \
    std::ostringstream oss;                             \
    oss << msg;                                         \
    std::string str = "Assertion failed: " + oss.str(); \
    std::cerr << str << std::endl;                      \
    THROW(str); }										\
} while(0)

// Assert with message printing and logging
#define ASSERT_LOG(cond, msg)                           \
do {                                                    \
    if (!(cond)) {                                      \
    logstream log(LOGGER_FILE);                         \
    std::ostringstream oss;                             \
    oss << msg;                                         \
    std::string str = "Assertion failed: " + oss.str(); \
    log << str << std::endl;                            \
    THROW(str); }										\
} while(0)

// Assert with message printing and logging (no throw)
#define ASSERT_WARN(cond, msg)                          \
do {                                                    \
    if (!(cond)) {                                      \
    logstream log(LOGGER_FILE);                         \
    std::ostringstream oss;                             \
    oss << msg;                                         \
    std::string str = "Warning: " + oss.str();          \
    log << str << std::endl; }                          \
} while(0)

// Calls return with specified error if < 0
#define RETURN_ERROR(error)                             \
do {                                                    \
    if (error < 0) { return error; }                    \
} while (0)

#endif/*COMMON_CPP_TESTING_H*/