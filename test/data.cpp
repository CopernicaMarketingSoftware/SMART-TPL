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
    string input("{$null}\n{$bool}\n{$int}\n{$string}\n{foreach $i in $vector}{$i}\n{/foreach}\n{foreach $map as $key => $value}{$key}={$value}\n{/foreach}");
    Template tpl((Buffer(input)));

    Variant::Value map;
    map["null"] = nullptr;
    map["bool"] = true;
    map["int"] = 12345;
    map["string"] = "Testing 1 2 3";
    std::vector<Variant::Value> list({1, 2, 3, 4, 5});
    map["vector"] = list;
    map["map"] = std::map<std::string, Variant::Value>({{"first", 1},{"second", 2}});
    Data data(map);
    string expectedOutput("\n1\n12345\nTesting 1 2 3\n1\n2\n3\n4\n5\n\nfirst=1\nsecond=2\n");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}