/**
 *  Modifier.cpp
 *
 *  Test the built-in modifiers
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Modifier, ToUpper)
{
    string input("{$var|toupper}\n{$var|upper}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("VARIABLE\nVARIABLE");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, ToLower)
{
    string input("{$var|tolower}\n{$var|lower}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("variable\nvariable");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, Cat)
{
    string input("{$var|cat:\" 1 2 3\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Testing");

    string expectedOutput("Testing 1 2 3");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, CountCharacters)
{
    string input("{$var|count_characters}\n{$var|count_characters:true}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Cold Wave Linked to Temperatures.");

    string expectedOutput("29\n33");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, CountParagraphs)
{
    string input("{$var|count_paragraphs}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "War Dims Hope for Peace. Child's Death Ruins Couple's Holiday.\n\n"
                       "Man is Fatally Slain. Death Causes Loneliness, Feeling of Isolation.");

    string expectedOutput("2");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, Default)
{
    string input("{$var|default:\"default string\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    EXPECT_EQ("default string", tpl.process());
    Data data;
    data.assign("var", "string");
    EXPECT_EQ("string", tpl.process(data));

    compile(tpl);
}

TEST(Modifier, Escape)
{
    string input("{$var|escape:\"html\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "<b>This is bold</b>");

    string expectedOutput("&lt;b&gt;This is bold&lt;/b&gt;");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}

TEST(Modifier, Indent)
{
    string input("{$var|indent}\n{$var|indent:1:\"\t\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Test");

    string expectedOutput("    Test\n\tTest");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}

TEST(Modifier, Replace)
{
    string input("{$var|replace:\"Garden\":\"Vineyard\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Child\'s Stool Great for Use in Garden.");

    string expectedOutput("Child\'s Stool Great for Use in Vineyard.");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}

TEST(Modifier, Nl2br)
{
    string input("{$var|nl2br}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "This is just a simple\ntest text.");

    string expectedOutput("This is just a simple<br />test text.");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}

TEST(Modifier, Spacify)
{
    string input("{$var|spacify}\n{$var|spacify:\"^^\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Testing 1 2 3");

    string expectedOutput("T e s t i n g   1   2   3\nT^^e^^s^^t^^i^^n^^g^^ ^^1^^ ^^2^^ ^^3");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}

TEST(Modifier, Truncate)
{
    string input("{$var|truncate}\n{$var|truncate:13}\n{$var|truncate:13:\"\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "This is just a simple test sentence.");

    string expectedOutput("This is just a simple test sentence.\nThis is ju...\nThis is just ");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}