/**
 *  Data.cpp
 *
 *  Data related tests, this will mostly test the VARIANT-CPP -> SmartTpl::Data feature
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

using namespace SmartTpl;
using namespace std;

TEST(Data, VariantMap)
{
    string input("{$null}\n{$bool}\n{$int}\n{$string}");
    Template tpl((Buffer(input)));

    ::Variant::Value map;
    map["null"] = nullptr;
    map["bool"] = true;
    map["int"] = 12345;
    map["string"] = "Testing 1 2 3";
    Data data(map);
    string expectedOutput("\n1\n12345\nTesting 1 2 3");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}