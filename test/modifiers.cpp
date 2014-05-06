/**
 *  Modifiers.cpp
 *
 *  Modifier related tests
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Modifiers, ChainedModifiers) {
    string input("{$var|tolower|toupper|tolower}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("variable");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
};

class TestModifier : public Modifier {
public:
    enum Mode {
        NumericMode,
        StringMode,
    };
    TestModifier(Mode mode) : Modifier(), _mode(mode) {};
    virtual ~TestModifier() {};

    virtual Variant modify(Value *input, const Parameters *params) override
    {
        switch (_mode) {
            case NumericMode:
                EXPECT_EQ(4, params->size());
                for (int i = 0; i < params->size(); ++i)
                {
                    EXPECT_EQ(i, params->get(i).toNumeric());
                }
                break;
            case StringMode:
                EXPECT_EQ(1, params->size());
                EXPECT_STREQ("test", params->get(0).toString());
                EXPECT_EQ(4, params->get(0).size());
                break;
        };
        return string(input->toString(), input->size());
    }
private:
    const Mode _mode;
};

TEST(Modifiers, Parameters)
{
    string input("{$var|test:0:1:2:3}");
    Buffer buffer(input);
    Template tpl(buffer);

    TestModifier test(TestModifier::NumericMode);
    Data data;
    data.modifier("test", &test)
        .assign("var", "Test");
    string expectedOutput("Test");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifiers, ParametersChainingNoParameters)
{
    string input("{$var|toupper|test:0:1:2:3}");
    Buffer buffer(input);
    Template tpl(buffer);

    TestModifier test(TestModifier::NumericMode);
    Data data;
    data.modifier("test", &test)
        .assign("var", "Test");
    string expectedOutput("TEST");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifiers, ParametersChainingParameters)
{
    string input("{$var|test:0:1:2:3|test:0:1:2:3}");
    Buffer buffer(input);
    Template tpl(buffer);

    TestModifier test(TestModifier::NumericMode);
    Data data;
    data.modifier("test", &test)
        .assign("var", "Test");
    string expectedOutput("Test");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, ParametersString)
{
    string input("{$var|test:\"test\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    TestModifier test(TestModifier::StringMode);
    Data data;
    data.modifier("test", &test)
        .assign("var", "Test");

    string expectedOutput("Test");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

// From here on the actual builtin modifiers are tested

TEST(Modifiers, ToUpper)
{
    string input("{$var|toupper}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("VARIABLE");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifiers, ToLower)
{
    string input("{$var|tolower}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("variable");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifiers, Cat)
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