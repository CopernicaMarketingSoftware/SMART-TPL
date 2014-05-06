#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

TEST(Syntax, WithoutElse) {
    string input("{if true}true{elseif true}true{/if}");
    Buffer buffer(input);
    Template tpl(buffer);
};

TEST(Syntax, AssignTo) {
    string input("{assign 1 to $var}");
    Buffer buffer(input);
    Template tpl(buffer);
};

TEST(Syntax, Assign) {
    string input("{$var = 1}");
    Buffer buffer(input);
    Template tpl(buffer);
};

TEST(Syntax, AssignNoSpaces) {
    string input("{$var=1}");
    Buffer buffer(input);
    Template tpl(buffer);
};