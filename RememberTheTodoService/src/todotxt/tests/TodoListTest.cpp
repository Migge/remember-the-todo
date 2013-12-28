#include <gtest/gtest.h>
#include "../TodoList.h"

#define RAWLIST  "Äta frukost\n(A) Handla @Errands\nPryla Björk +Viktigt\nHej"
#define RAWLIST2 "  Äta frukost\nHandla\n Hej\n+Viktigt Pryla Björk"

TEST(TodoListTest, TestBuildNewList) {
  RTT::TodoList list;
  RTT::TodoItem item;
  list.buildList(RAWLIST);
  item.buildItem("  (A)  @Errands  Handla ");
  EXPECT_TRUE(list[1] == item);
}

TEST(TodoListTest, TestListSize) {
  RTT::TodoList list;
  list.buildList(RAWLIST);
  EXPECT_TRUE(list.size() == 4);
}

TEST(TodoListTest, TestNrOfRemovedItems) {
  RTT::TodoList list;
  RTT::TodoItem item;
  list.buildList(RAWLIST);
  list.buildList(RAWLIST2);
  EXPECT_TRUE(list.nrOfRemovedItems() == 1);
}

TEST(TodoListTest, TestRemovedItem) {
  RTT::TodoList list;
  list.buildList(RAWLIST);
  list.buildList(RAWLIST2);
  RTT::TodoItem item;
  item.buildItem("(A) Handla @Errands");
  RTT::TodoItem removedItem = list.getRemovedItem(0);
  EXPECT_TRUE(item == removedItem);
}
