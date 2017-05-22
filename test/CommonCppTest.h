#ifndef COMMON_CPP_TEST_H
#define COMMON_CPP_TEST_H

#include "CommonCpp.h"

// Boost unittest
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Common (C++) Unit Tests
#include <boost/test/unit_test.hpp>

static const ChokePoint chokepoint;
static const COXS2V coxs2v;

#endif/*COMMON_CPP_TEST_H*/