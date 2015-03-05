/**
 *  Invalid_Syntax.cpp
 *
 *  Unit tests that tests if certain syntax which should be invalid is in fact invalid
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(InvalidSyntax, Mode)
{
    string input("{mode=html}");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, Escape)
{
    string input("{escape}");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, UnclosedIf)
{
    string input("{if }");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, NoEndIf)
{
    string input("{if true}true");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, IfElseNoEndIf)
{
    string input("{if true}true{else}false");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, ElseIfNoEndIf)
{
    string input("{if true}true{elseif true}also true{else}false");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, ForEachNoEndForEach)
{
    string input("{foreach $var in $map}loop");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, ForEachAsNoEndForEach)
{
    string input("{foreach $map as $var}loop");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, ForEachWithKeysNoEndForEach)
{
    string input("{foreach $map as $key => $var}loop");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, ForEachElseNotEndForEach)
{
    string input("{foreach $var in $map}loop{foreachelse}else");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, AssignToNoExpression)
{
    string input("{assign 1 to");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, AssignNoExpression)
{
    string input("{$var =");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, ArrayAccess)
{
    string input("{$var[0");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, KeyArrayAccess)
{
    string input("{$var[\"key\"");
    EXPECT_THROW(Template((Buffer(input))), CompileError);
}

TEST(InvalidSyntax, NotExistingFunction)
{
    string input("{invalid}");
    EXPECT_THROW(Template tpl((Buffer(input)));, CompileError);
}

TEST(InvalidSyntax, InvalidExpression)
{
    string input("{$1 + 3}");
    EXPECT_THROW(Template tpl((Buffer(input)));, CompileError);
}

/**
 *  Break down tests will simply start removing characters up until some point and
 *  expect them to fail on pretty much everything on their way.
 */

TEST(InvalidSyntax, BreakDownForEach)
{
    string input("{foreach $map as $key => $var}{/foreach}");
    std::string::size_type len = input.size();
    for (std::string::size_type i = len; i > 0; --i)
    {
        string tpl(input.substr(0, i));
        EXPECT_THROW(Template((Buffer(tpl))), CompileError)
                     << "The following template didn't fail to compile:" << std::endl << std::endl << tpl << std::endl;
    }
}

TEST(InvalidSyntax, BreakDownAssign)
{
    string input("{assign 5 to $five}");
    EXPECT_NO_THROW(Template((Buffer(input))));
    std::string::size_type len = input.size() - 1;
    for (std::string::size_type i = len; i > 0; --i)
    {
        string tpl(input.substr(0, i));
        EXPECT_THROW(Template((Buffer(tpl))), CompileError)
                     << "The following template didn't fail to compile:" << std::endl << std::endl << tpl << std::endl;
    }
}