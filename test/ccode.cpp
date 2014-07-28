/**
 *  CCode.cpp
 *
 *  C code related unit tests, mostly to check if they generate the correct code
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(CCode, ForEach)
{
    string input("{foreach $key in $map}key: {$key}\n{/foreach}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n{\n"
    "void *iterator = callbacks->create_iterator(userdata,callbacks->variable(userdata,\"map\",3));\n"
    "while (callbacks->valid_iterator(userdata,iterator)) {\n"
    "callbacks->assign(userdata,\"key\",3,callbacks->iterator_value(userdata,iterator));\n"
    "callbacks->write(userdata,\"key: \",5);\ncallbacks->output(userdata,callbacks->variable(userdata,\"key\",3),1);\n"
    "callbacks->write(userdata,\"\\n\",1);\ncallbacks->iterator_next(userdata,iterator);\n}\n"
    "callbacks->delete_iterator(userdata,iterator);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, ForEachWithKeys)
{
    string input("{foreach $map as $key => $value}key: {$key}\nvalue: {$value}{/foreach}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n{\n"
    "void *iterator = callbacks->create_iterator(userdata,callbacks->variable(userdata,\"map\",3));\n"
    "while (callbacks->valid_iterator(userdata,iterator)) {\n"
    "callbacks->assign(userdata,\"key\",3,callbacks->iterator_key(userdata,iterator));\n"
    "callbacks->assign(userdata,\"value\",5,callbacks->iterator_value(userdata,iterator));\n"
    "callbacks->write(userdata,\"key: \",5);\ncallbacks->output(userdata,callbacks->variable(userdata,\"key\",3),1);\n"
    "callbacks->write(userdata,\"\\n\",1);\ncallbacks->write(userdata,\"value: \",7);\n"
    "callbacks->output(userdata,callbacks->variable(userdata,\"value\",5),1);\n"
    "callbacks->iterator_next(userdata,iterator);\n}\ncallbacks->delete_iterator(userdata,iterator);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, ForEachElse)
{
    string input("{foreach $key in $map}key: {$key}\n{foreachelse}else{/foreach}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n{\n"
    "void *iterator = callbacks->create_iterator(userdata,callbacks->variable(userdata,\"map\",3));\n"
    "if (!callbacks->valid_iterator(userdata,iterator)) {\ncallbacks->write(userdata,\"else\",4);\n} else {\n"
    "while (callbacks->valid_iterator(userdata,iterator)) {\n"
    "callbacks->assign(userdata,\"key\",3,callbacks->iterator_value(userdata,iterator));\n"
    "callbacks->write(userdata,\"key: \",5);\ncallbacks->output(userdata,callbacks->variable(userdata,\"key\",3),1);\n"
    "callbacks->write(userdata,\"\\n\",1);\ncallbacks->iterator_next(userdata,iterator);\n}\n}\n"
    "callbacks->delete_iterator(userdata,iterator);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, SingleModifier)
{
    string input("{$var|toupper}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n{\nconst void *o = NULL;\n"
    "o = callbacks->modify_variable(userdata,callbacks->variable(userdata,\"var\",3),callbacks->modifier(userdata,\"toupper\",7),NULL);\n"
    "callbacks->output(userdata,o,1);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, ChainedModifiers)
{
    string input("{$var|toupper|tolower|toupper|tolower}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n{\nconst void *o = NULL;\n"
    "o = callbacks->modify_variable(userdata,callbacks->variable(userdata,\"var\",3),callbacks->modifier(userdata,\"toupper\",7),NULL);\n"
    "o = callbacks->modify_variable(userdata,o,callbacks->modifier(userdata,\"tolower\",7),NULL);\n"
    "o = callbacks->modify_variable(userdata,o,callbacks->modifier(userdata,\"toupper\",7),NULL);\n"
    "o = callbacks->modify_variable(userdata,o,callbacks->modifier(userdata,\"tolower\",7),NULL);\n"
    "callbacks->output(userdata,o,1);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, IfElse)
{
    string input("{if $variable}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->to_boolean(userdata,callbacks->variable(userdata,\"variable\",8))){\n"
    "callbacks->write(userdata,\"true\",4);\n}else{\ncallbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, ElseIf)
{
    string input("{if $variable}first is true{elseif $othervariable}second is true{else}nothing is true{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->to_boolean(userdata,callbacks->variable(userdata,\"variable\",8))){\n"
    "callbacks->write(userdata,\"first is true\",13);\n}else{\n"
    "if (callbacks->to_boolean(userdata,callbacks->variable(userdata,\"othervariable\",13))){\n"
    "callbacks->write(userdata,\"second is true\",14);\n}else{\n"
    "callbacks->write(userdata,\"nothing is true\",15);\n}\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, VarGreaterThen)
{
    string input("{if $age > 18}You are over 18 years old.{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->to_numeric(userdata,callbacks->variable(userdata,\"age\",3))>18){\n"
    "callbacks->write(userdata,\"You are over 18 years old.\",26);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, VarGreaterThenNegativeNumber)
{
    string input("{if $age > -1}You are alive..{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->to_numeric(userdata,callbacks->variable(userdata,\"age\",3))>-1){\n"
    "callbacks->write(userdata,\"You are alive..\",15);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, LiteralArrayAccess)
{
    string input("{$map[0]}\n{$map.anothermember}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->output(userdata,callbacks->member_at(userdata,callbacks->variable(userdata,\"map\",3),0),1);\n"
    "callbacks->write(userdata,\"\\n\",1);\n"
    "callbacks->output(userdata,callbacks->member(userdata,callbacks->variable(userdata,\"map\",3),\"anothermember\",13),1);\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, NumericComparison)
{
    string input("{if 10 == 100}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (10==100){\ncallbacks->write(userdata,\"true\",4);\n}else{\n"
    "callbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, BoolComparison)
{
    string input("{if true == false}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (1==0){\ncallbacks->write(userdata,\"true\",4);\n}else{\ncallbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, StringComparison)
{
    string input("{if \"string1\" == \"string2\"}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->strcmp(userdata,\"string1\",7,\"string2\",7) == 0){\ncallbacks->write(userdata,\"true\",4);\n}else{\n"
    "callbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, StringComparisonNotEquals)
{
    string input("{if \"string1\" != \"string2\"}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->strcmp(userdata,\"string1\",7,\"string2\",7) != 0){\n"
    "callbacks->write(userdata,\"true\",4);\n}else{\ncallbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, AssignValue)
{
    string input("{assign \"string\" to $value}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->assign_string(userdata,\"value\",5,\"string\",6);\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, AssignValueIs)
{
    string input("{$value = \"string\"}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->assign_string(userdata,\"value\",5,\"string\",6);\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, LiteralStringsWeirdCharacters)
{
    string input("{if \"?_\\\"<test>\" == \"-\'/%#^&\"}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->strcmp(userdata,\"?_\\\"<test>\",9,\"-\\'/%#^&\",7) == 0){\n"
    "callbacks->write(userdata,\"true\",4);\n}else{\ncallbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, LiteralEmptyString)
{
    string input("{if \"\" == \"not empty\"}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->strcmp(userdata,NULL,0,\"not empty\",9) == 0){\n"
    "callbacks->write(userdata,\"true\",4);\n}else{\ncallbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, ModifierParameters)
{
    string input("{$var|substring:1:5}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n{\nconst void *o = NULL;\n"
    "{\nvoid *p = callbacks->create_params(userdata,2);\n"
    "callbacks->params_append_numeric(userdata,p,1);\n"
    "callbacks->params_append_numeric(userdata,p,5);\n"
    "o = callbacks->modify_variable(userdata,callbacks->variable(userdata,\"var\",3),callbacks->modifier(userdata,\"substring\",9),p);\n"
    "callbacks->delete_params(userdata,p);\n}\n"
    "callbacks->output(userdata,o,1);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, Unicode)
{
    string input("이것은 단순한 유니 테스트입니다 ..");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->write(userdata,\"\xEC\x9D\xB4\xEA\xB2\x83\xEC\x9D\x80 \xEB\x8B\xA8\xEC"
    "\x88\x9C\xED\x95\x9C \xEC\x9C\xA0\xEB\x8B\x88 \xED\x85\x8C\xEC\x8A\xA4\xED\x8A\xB8"
    "\xEC\x9E\x85\xEB\x8B\x88\xEB\x8B\xA4 ..\",48);\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, LiteralStringUnicode)
{
    string input("{if \"\" == \"이것은 단순한 유니 테스트입니다 ..\"}true{else}false{/if}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "if (callbacks->strcmp(userdata,NULL,0,\"\xEC\x9D\xB4\xEA\xB2\x83\xEC\x9D\x80 "
    "\xEB\x8B\xA8\xEC\x88\x9C\xED\x95\x9C \xEC\x9C\xA0\xEB\x8B\x88 \xED\x85\x8C\xEC"
    "\x8A\xA4\xED\x8A\xB8\xEC\x9E\x85\xEB\x8B\x88\xEB\x8B\xA4 ..\",48) == 0){\n"
    "callbacks->write(userdata,\"true\",4);\n}else{\ncallbacks->write(userdata,\"false\",5);\n}\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, TemplateMode)
{
    string input("{mode=test}{$var}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->output(userdata,callbacks->variable(userdata,\"var\",3),1);\n}\n"
    "const char *mode = \"test\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());
    EXPECT_EQ("test", tpl.encoding());

    compile(tpl);
}

TEST(CCode, Encoded)
{
    string input("{mode=html}<b>This is bold</b>");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->write(userdata,\"<b>This is bold</b>\",19);\n}\n"
    "const char *mode = \"html\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());
    EXPECT_EQ("html", tpl.encoding());

    compile(tpl);
}

TEST(CCode, LiteralBlock)
{
    string input("{literal}{width=100;}{$var}{if}1 2 3{/literal}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->write(userdata,\"{width=100;}{$var}{if}1 2 3\",27);\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}

TEST(CCode, OutputMath)
{
    string input("1+3-2*10={1+ 3- 2*10}");
    Template tpl((Buffer(input)));

    string expectedOutput("#include <smarttpl/callbacks.h>\n"
    "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {\n"
    "callbacks->write(userdata,\"1+3-2*10=\",9);\ncallbacks->output_numeric(userdata,1+3-2*10);\n}\n"
    "const char *mode = \"raw\";\n");
    EXPECT_EQ(expectedOutput, tpl.compile());

    compile(tpl);
}