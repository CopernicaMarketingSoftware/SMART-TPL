#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

TEST(Callbacks, SimpleCallback) {
  string input("{$name}");
  Buffer buffer(input);
  Template tpl(buffer);

  Data data;
  data.callback("name",[](){ return "Name"; });

  string expectedOutput("Name");
  EXPECT_EQ(tpl.process(data), expectedOutput);
};

TEST(Callbacks, CallbackCaching) {
  string input("{$name} {$name}");
  Buffer buffer(input);
  Template tpl(buffer);

  int counter = 0;
  Data data;
  data.callback("name", [&counter](){
      counter++;
      return "Name";
    }, true);

  string expectedOutput("Name Name");
  EXPECT_EQ(tpl.process(data), expectedOutput);
  EXPECT_EQ(counter, 1);
};