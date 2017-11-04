#include "testing.h"
#include "logging.h"

int passThroughDisplayTestStatus(std::string testName, int error, std::string reason)
{
    logstream logger(LOGGER_FILE);
    reason = reason.empty() ? reason : " [" + reason + "]";
    if      (error == SKIPPED)  logger << "Test '" << testName << "' skipped"  << reason << "." << std::endl;
    else if (error == OBSOLETE) logger << "Test '" << testName << "' obsolete" << reason << "." << std::endl;
    else if (error == PASSED)   logger << "Test '" << testName << "' passed"   << reason << "." << std::endl;
    else                        logger << "Test '" << testName << "' failed (" << std::to_string(error) << ")." << std::endl;
    return error;
}

bool checkPathEndSlash(std::string path)
{
    char end = *path.rbegin();
    return end == '/' || end == '\\';
}
