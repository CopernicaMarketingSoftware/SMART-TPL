/**
 *  Modifier.cpp
 *
 *  Test the built-in modifiers
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Modifier, ToUpper)
{
    string input("{$var|toupper}\n{$var|upper}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("VARIABLE\nVARIABLE");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, ToLower)
{
    string input("{$var|tolower}\n{$var|lower}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("variable\nvariable");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Cat)
{
    string input("{$var|cat:\" 1 2 3\"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Testing");

    string expectedOutput("Testing 1 2 3");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, CountCharacters)
{
    string input("{$var|count_characters}\n{$var|count_characters:true}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Cold Wave Linked to Temperatures.");

    string expectedOutput("29\n33");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, CountParagraphs)
{
    string input("{$var|count_paragraphs}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "War Dims Hope for Peace. Child's Death Ruins Couple's Holiday.\n\n"
                       "Man is Fatally Slain. Death Causes Loneliness, Feeling of Isolation.");

    string expectedOutput("2");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Default)
{
    string input("{$var|default:\"default string\"}");
    Template tpl((Buffer(input)));

    EXPECT_EQ("default string", tpl.process());
    Data data;
    data.assign("var", "string");
    EXPECT_EQ("default string", tpl.process());
    EXPECT_EQ("string", tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ("default string", library.process());
        EXPECT_EQ("string", library.process(data));
    }
}

TEST(Modifier, Escape)
{
    string input("{$var|escape:\"html\"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "<b>This is bold</b>");

    string expectedOutput("&lt;b&gt;This is bold&lt;/b&gt;");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Indent)
{
    string input("{$var|indent}\n-\n{$var|indent:1:\"\t\"}\n-\n{$var2|indent:1:\"\t\"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Test")
        .assign("var2", "Testing\n1 2 3\ntest");

    string expectedOutput("    Test\n-\n\tTest\n-\n\tTesting\n\t1 2 3\n\ttest");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Replace)
{
    string input("{$var|replace:\"Garden\":\"Vineyard\"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Child\'s Stool Great for Use in Garden.");

    string expectedOutput("Child\'s Stool Great for Use in Vineyard.");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Nl2br)
{
    string input("{$var|nl2br}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "This is just a simple\ntest text.");

    string expectedOutput("This is just a simple<br />test text.");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Spacify)
{
    string input("{$var|spacify}\n{$var|spacify:\"^^\"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Testing 1 2 3");

    string expectedOutput("T e s t i n g   1   2   3\nT^^e^^s^^t^^i^^n^^g^^ ^^1^^ ^^2^^ ^^3");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Truncate)
{
    string input("{$var|truncate}\n{$var|truncate:13}\n{$var|truncate:13:\"\"}\n{$var|truncate:13:\"...\":true}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "This is just a simple test sentence.");

    string expectedOutput("This is just a simple test sentence.\nThis is...\nThis is just\nThis is ju...");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Strlen)
{
    string input("{$var|strlen}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Testing 1 2 3");

    string expectedOutput("13");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Count)
{
    string input("{$var|count}");
    Template tpl((Buffer(input)));

    std::vector<VariantValue> list;
    for (int i = 0; i < 10; ++i) list.push_back(i);

    Data data;
    data.assign("var", list);

    string expectedOutput("10");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, CountWords)
{
    string input("{$var|count_words}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "This is just a simple test sentence.");

    string expectedOutput("7");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, UcFirst)
{
    string input("{$var|ucfirst}.");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "sir");

    string expectedOutput("Sir.");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Trim)
{
    string input("{$var|trim}\n{$var|trim:\" \"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "  \tTest\n\t  ");

    string expectedOutput("Test\n\tTest\n\t");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, RegexReplace)
{
    string input("{$var|regex_replace:\"a|e|i|o|u\":\"*\"}\n{$var|regex_replace:\"a|e|i|o|u\":\"[$&]\"}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Quick brown fox");

    string expectedOutput("Q**ck br*wn f*x\nQ[u][i]ck br[o]wn f[o]x");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, SubStr)
{
    string input("{$var|substr:1}\n{$var|substr:1:3}\n{$var|substr:0:4}\n{$var|substr:0:8}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "abcdef");

    string expectedOutput("bcdef\nbcd\nabcd\nabcdef");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, SubStrOutOfRange)
{
    string input("{$var|substr:10:1}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "abcdef");

    string expectedOutput("abcdef");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, StrStr)
{
    string input("{$var|strstr:\"@\"}\n{$var|strstr:\"@\":true}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "name@example.com");

    string expectedOutput("@example.com\nname");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Urlencode)
{
    string input("http://httpbin.org/get?{$var|urlencode}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "foo&bar=some/value");

    string expectedOutput("http://httpbin.org/get?foo%26bar%3Dsome%2Fvalue");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Urldecode)
{
    string input("{$var|urldecode}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "foo%26bar%3Dsome%2Fvalue");

    string expectedOutput("foo&bar=some/value");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, MD5)
{
    string input("{$var|md5}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Test string");

    string expectedOutput("0fd3dbec9730101bff92acc820befc34");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, SHA1)
{
    string input("{$var|sha1}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Test string");

    string expectedOutput("18af819125b70879d36378431c4e8d9bfa6a2599");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, SHA256)
{
    string input("{$var|sha256}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Test string");

    string expectedOutput("a3e49d843df13c2e2a7786f6ecd7e0d184f45d718d1ac1a8a63e570466e489dd");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, SHA512)
{
    string input("{$var|sha512}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "Test string");

    string expectedOutput("811aa0c53c0039b6ead0ca878b096eed1d39ed873fd2d2d270abfb9ca620d3ed561c565d6dbd1114c323d38e3f59c00df475451fc9b30074f2abda3529df2fa7");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Base64Encoding)
{
    string input("{$var|base64_encode}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "test");

    string expectedOutput("dGVzdA==");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Modifier, Base64EncodingBig)
{
    string input("{$var|base64_encode}");
    Template tpl((Buffer(input)));

    Data data;
    std::string str(1024 * 1024 * 16, 'a'); // 16MB string
    data.assign("var", str);

    EXPECT_GT(tpl.process(data).size(), str.size());

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_GT(library.process(data).size(), str.size());
    }
}

TEST(Modifier, Base64Decoding)
{
    string input("{$var|base64_decode}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "dGVzdA==");

    string expectedOutput("test");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}