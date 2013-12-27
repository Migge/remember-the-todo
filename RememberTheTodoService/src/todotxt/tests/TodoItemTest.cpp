#include <gtest/gtest.h>
#include "../TodoItem.h"

TEST(TodoItemTest, TestConstructor) {
  TodoItem item("hej");
  EXPECT_STREQ(item.getAction().toLatin1().data(), "hej");
}

TEST(TodoItemTest, TestItemBuilder) {
  TodoItem item;
  item.buildItem("   (B) Pryla @Home    Björk    +Viktigt  ");
  
  EXPECT_EQ(item.getPriority(), RTT::B);
  EXPECT_STREQ(item.getAction().toUtf8().data(), "Pryla Björk");
  EXPECT_STREQ(item.getContext().toUtf8().data(), "@Home");
  EXPECT_STREQ(item.getProject().toUtf8().data(), "+Viktigt");
}

TEST(TodoItemTest, TestItemBuilderWrongPriority) {
  TodoItem item;
  item.buildItem("   Pryla (B) Björk @Home +Viktigt ");
  EXPECT_NE(item.getPriority(), RTT::B);
}


//TEST(TodoItemTest, Test

// test not initial priority should fail
