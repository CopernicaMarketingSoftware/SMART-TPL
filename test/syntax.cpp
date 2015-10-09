/**
 *  Syntax.cpp
 *
 *  Unit tests that tests if certain syntax which should be valid is in fact valid
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Syntax, Empty)
{
    string input;
    Template tpl((Buffer(input)));

    string expectedOutput;
    EXPECT_EQ(expectedOutput, tpl.process());

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process());
    }
}

TEST(Syntax, Mode)
{
    string input("{mode=html}echo"); // echo is purely there as we do at least need 1 statement
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, Escape)
{
    string input("{escape}echo");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, Raw)
{
    string input("{$var}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, SingleIf)
{
    string input("{if true}true{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, EndIf)
{
    string input("{if true}true{endif}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, IfElse)
{
    string input("{if true}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ElseIf)
{
    string input("{if true}true{elseif true}also true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

// In a previous version you were unable to use elseif without putting an else block after it
TEST(Syntax, WithoutElse)
{
    string input("{if true}true{elseif true}true{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, IfNotTrue)
{
    string input("{if not true}false{else}true{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, IfNotVar)
{
    string input("{if !$var}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, IfNotModifier)
{
    string input("{if not $var|empty}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ForEach)
{
    string input("{foreach $var in $map}loop{/foreach}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ForEachAs)
{
    string input("{foreach $map as $var}loop{/foreach}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ForEachWithKeys)
{
    string input("{foreach $map as $key => $var}loop{/foreach}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ForEachElse)
{
    string input("{foreach $var in $map}loop{foreachelse}else{/foreach}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ForEachAsElse)
{
    string input("{foreach $map as $var}loop{foreachelse}else{/foreach}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ForEachWithKeysElse)
{
    string input("{foreach $map as $key => $var}loop{foreachelse}else{/foreach}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, AssignTo)
{
    string input("{assign 1 to $var}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, Assign)
{
    string input("{$var = 1}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, AssignNoSpaces)
{
    string input("{$var=1}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, ArrayAccess)
{
    string input("{$var[0]}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, KeyArrayAccess)
{
    string input("{$var[\"key\"]}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, NotExistingFunction)
{
    string input("{invalid}");
    EXPECT_THROW(Template tpl((Buffer(input)));, std::runtime_error);
}

TEST(Syntax, LiteralContentSpace)
{
    string input("{ width=100;}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, LiteralBlock)
{
    string input("{literal}{width=100;}{$test}1 2 3{/literal}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, Equals)
{
    string input("{if true eq true}true{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, NotEquals)
{
    string input("{if true ne false}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, GreaterThan)
{
    string input("{if 1 \tgte 2 OR 2 gt 1}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, GreaterThanElse)
{
    string input("{if 1 ge 1}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, LessThan)
{
    string input("{if 1 lt 2 and 2 lte 1}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, LessThanEquals)
{
    string input("{if 1 le 2}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, NonExistingOperator)
{
    string input("{if 1 notanoperator 2}true{else}false{/if}");
    EXPECT_THROW(Template tpl((Buffer(input)));, std::runtime_error);
}

TEST(Syntax, GreaterThanDouble)
{
    string input("{if 13.37 gte 3.14}true{else}false{/if}");
    Template tpl((Buffer(input)));
    compile(tpl);
}