#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Syntax, Empty)
{
    string input;
    Template tpl((Buffer(input)));
    compile(tpl);
}

TEST(Syntax, Mode)
{
    string input("{mode=html}");
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