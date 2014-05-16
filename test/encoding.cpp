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
    string input("<b>This is {$bold}</b>");
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

TEST(Encoding, HtmlToRaw)
{
    string input("{escape}<b>This is {$bold}</b>");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("bold", "<i>This should be escaped</i>");
    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->write(userdata,\"<b>This is \",11);\n"
    "callbacks->output(userdata,callbacks->variable(userdata,\"bold\",4));\n"
    "callbacks->write(userdata,\"</b>\",4);\n}\nconst char *mode = \"html\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    EXPECT_EQ("<b>This is &lt;i&gt;This should be escaped&lt;/i&gt;</b>", tpl.process(data));
    EXPECT_EQ("<b>This is <i>This should be escaped</i></b>", tpl.process(data, "raw"));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ("<b>This is &lt;i&gt;This should be escaped&lt;/i&gt;</b>", library.process(data)); // We compiled it in html mode so default is html
        EXPECT_EQ("<b>This is <i>This should be escaped</i></b>", library.process(data, "raw")); // We request raw mode, so it decodes it for us
    }
}