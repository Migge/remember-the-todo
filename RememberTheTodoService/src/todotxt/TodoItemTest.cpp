#include <gtest/gtest.h>
#include "TodoItem.h"

#define STANDARDITEM "   (B) Pryla @Home    Björk    +Viktigt  "

TEST(TodoItemTest, TestConstructor) {
  RTT::TodoItem item("hej");
  EXPECT_STREQ(item.getAction().toLatin1().data(), "hej");
}

TEST(TodoItemTest, TestPriority) {
  RTT::TodoItem item;
  item.buildItem(STANDARDITEM);
  EXPECT_EQ(item.getPriority(), RTT::B);
  EXPECT_STREQ(item.getAction().toUtf8().data(), "Pryla Björk");
  EXPECT_STREQ(item.getContext().toUtf8().data(), "@Home");
  EXPECT_STREQ(item.getProject().toUtf8().data(), "+Viktigt");
}

TEST(TodoItemTest, TestStandardPriority) {
  RTT::TodoItem item;
  item.buildItem(STANDARDITEM);
  EXPECT_EQ(item.getPriority(), RTT::B);
}

TEST(TodoItemTest, TestStandardAction) {
  RTT::TodoItem item;
  item.buildItem(STANDARDITEM);
  EXPECT_STREQ(item.getAction().toUtf8().data(), "Pryla Björk");
}

TEST(TodoItemTest, TestStandardContext) {
  RTT::TodoItem item;
  item.buildItem(STANDARDITEM);
  EXPECT_STREQ(item.getContext().toUtf8().data(), "@Home");
}

TEST(TodoItemTest, TestStandardProject) {
  RTT::TodoItem item;
  item.buildItem(STANDARDITEM);
  EXPECT_STREQ(item.getProject().toUtf8().data(), "+Viktigt");
}

TEST(TodoItemTest, TestWrongPriority) {
  RTT::TodoItem item;
  item.buildItem("   Pryla (B) Björk @Home +Viktigt ");
  EXPECT_NE(item.getPriority(), RTT::B);
}

TEST(TodoItemTest, TestPriorityA) {
  RTT::TodoItem item;
  item.buildItem("   (A) Björk @Home +Viktigt ");
  EXPECT_EQ(item.getPriority(), RTT::A);
}

TEST(TodoItemTest, TestPriorityG) {
  RTT::TodoItem item;
  item.buildItem("   (G) Björk @Home +Viktigt ");
  EXPECT_EQ(item.getPriority(), RTT::G);
}

TEST(TodoItemTest, TestPriorityZ) {
  RTT::TodoItem item;
  item.buildItem("   (Z) Björk @Home +Viktigt ");
  EXPECT_EQ(item.getPriority(), RTT::Z);
}

TEST(TodoItemTest, TestMultipleContextsFirstOK) {
  RTT::TodoItem item;
  item.buildItem("Handla @Errands @Work");
  EXPECT_STREQ(item.getContext().toUtf8().data(), "@Errands");
}

TEST(TodoItemTest, TestMultipleContextsSecondFail) {
  RTT::TodoItem item;
  item.buildItem("Handla @Errands @Work");
  EXPECT_STRNE(item.getContext().toUtf8().data(), "@Work");
}

TEST(TodoItemTest, TestEqualItems) {
  RTT::TodoItem item1, item2;
  item1.buildItem("(A) Hälsa på pappa @Errands +Kalle");
  item2.buildItem("   (A) Hälsa +Kalle på @Errands   pappa  ");
  EXPECT_TRUE(item1 == item2);
}

TEST(TodoItemTest, TestNotEqualItems) {
  RTT::TodoItem item1, item2;
  item1.buildItem("(A) Hälsa på pappa @Errands +Kalle");
  item2.buildItem("   (A) Hälsa +Kallee på @Errands   pappa  ");
  EXPECT_TRUE(item1 != item2);
}
