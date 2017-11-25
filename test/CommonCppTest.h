#ifndef COMMON_CPP_TEST_H
#define COMMON_CPP_TEST_H

#include "CommonCpp.h"

// Boost unittest
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Common (C++) Unit Tests
#include <boost/test/unit_test.hpp>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

#endif/*COMMON_CPP_TEST_H*/
