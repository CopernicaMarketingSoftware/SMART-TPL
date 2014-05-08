/**
 *  Encoding.cpp
 *
 *  Encoding related tests, these will obivously be executing templates
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

TEST(Encoding, Html)
{
    string input("{mode=raw}<b>This is bold</b>");
    Buffer buffer(input);
    Template tpl(buffer);

    string expectedOutput("&lt;b&gt;This is bold&lt;/b&gt;");
    EXPECT_EQ(expectedOutput, tpl.process("html"));
}

TEST(Encoding, HtmlToRaw)
{
    string input("{mode=html}&lt;b&gt;This is bold&lt;/b&gt;");
    Buffer buffer(input);
    Template tpl(buffer);

    string expectedOutput("<b>This is bold</b>");
    EXPECT_EQ(expectedOutput, tpl.process("raw"));
}