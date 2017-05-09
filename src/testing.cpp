#include "testing.h"
#include "logging.h"

int passThroughDisplayTestStatus(std::string testName, int error)
{
    logstream logger(LOGGER_FILE);
    if      (error == SKIPPED)  logger << "Test '" << testName << "' skipped." << std::endl;
    else if (error == OBSOLETE) logger << "Test '" << testName << "' obsolete." << std::endl;
    else if (error == PASSED)   logger << "Test '" << testName << "' passed." << std::endl;    
    else                        logger << "Test '" << testName << "' failed (" << std::to_string(error) << ")." << std::endl;
    return error;
}

bool checkPathEndSlash(std::string path)
{
    char end = *path.rbegin();
    return end == '/' || end == '\\';
}