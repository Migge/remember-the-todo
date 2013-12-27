#include <gtest/gtest.h>
#include "../TodoItem.h"

TEST(TodoItemTest, TestConstructor) {
  TodoItem item("hej");
  EXPECT_STREQ(item.getAction().c_str(), std::string("hej").c_str());
}

//TEST(TodoItemTest, Test
