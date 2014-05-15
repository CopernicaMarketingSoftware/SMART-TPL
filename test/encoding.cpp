/**
 *  Encoding.cpp
 *
 *  Encoding related tests, these will obivously be executing templates
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Encoding, Html)
{
    string input("{mode=raw}<b>This is {$bold}</b>");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("bold", "<i>This should be escaped</i>");
    string expectedOutput("<b>This is &lt;i&gt;This should be escaped&lt;/i&gt;</b>");
    string expectedOutputRaw("<b>This is <i>This should be escaped</i></b>");
    EXPECT_EQ(expectedOutput, tpl.process(data, "html"));
    EXPECT_EQ(expectedOutputRaw, tpl.process(data, "raw"));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data, "html"));
        EXPECT_EQ(expectedOutputRaw, library.process(data, "raw"));
    }
}

TEST(Encoding, DISABLED_HtmlToRaw)
{
    string input("{mode=html}<b>This is bold</b>");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->write(userdata,\"&lt;b&gt;This is bold&lt;/b&gt;\",31);\n}\n"
    "const char *mode = \"html\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ("&lt;b&gt;This is bold&lt;/b&gt;", library.process()); // We compiled it in html mode so default is html
        EXPECT_EQ("<b>This is bold</b>", library.process("raw")); // We request raw mode, so it decodes it for us
    }
}