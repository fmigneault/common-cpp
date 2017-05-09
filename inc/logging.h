/* -------------------------
Logging/printing operations
------------------------- */
#ifndef COMMON_CPP_LOGGING_H
#define COMMON_CPP_LOGGING_H

// required magic!
#define __STDC_WANT_LIB_EXT1__ 1

#include "types.h"

#include <bitset>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

const std::string WINDOW_NAME = "Display";
const std::string LOGGER_FILE = "output.txt";

std::string currentTimeStamp();

class logstream
{
public:
    bool useConsoleOutput;
    bool useFileOutput;
    std::ofstream ofss;
    logstream(std::string filepath, bool useConsoleOutput = true, bool useFileOutput = true);
    ~logstream(void);
    logstream& operator<< (std::ostream& (*pfun)(std::ostream&));
};

template <class T>
inline logstream& operator<< (logstream& log, const T& val)
{
    if (log.useFileOutput)      log.ofss << val;
    if (log.useConsoleOutput)   std::cout << val;
    return log;
}

template <class T>
inline logstream& operator<< (logstream& log, const std::vector<T>& v)
{
    std::ostringstream oss;
    oss << "[";
    typename std::vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end()-1; ++it)
        oss << *it << " ";
    oss << *it << "]";

    std::string s = oss.str();
    if (log.useFileOutput)      log.ofss << s;
    if (log.useConsoleOutput)   std::cout << s;
    return log;
}

std::string featuresToVectorString(FeatureVector features);
std::string featuresToSvmString(FeatureVector features, int label);

template <const int BIT_SIZE>
std::string displayAsBinary(const int option, bool displayNumeric)
{
    std::stringstream ss;
    std::bitset<BIT_SIZE> binOption(option);
    ss << binOption;
    if (displayNumeric) ss << " (" << option << ")";
    return ss.str();
}

#endif/*COMMON_CPP_LOGGING_H*/
