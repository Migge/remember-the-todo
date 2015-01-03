#include <gtest/gtest.h>
#include "TodoList.h"

#define RAWLIST1 "Äta frukost\n(A) Handla @Errands\nPryla Björk +Viktigt\nHej"
#define RAWLIST2 "  Äta frukost\nHandla\n Hej\n+Viktigt Pryla Björk"

#define RAWLIST_SAME1 "  Äta frukost\nHandla\n Hej\n"
#define RAWLIST_SAME2 "  Handla\nÄta frukost   \n Hej\n"
#define RAWLIST_WRONG1 "  Äta frukost\nHandla\n Hejj\n"


#define ITEM1 "  (A)  @Errands  Handla "

TEST(TodoListTest, TestBuildNewList) {
  RTT::TodoList list;
  RTT::TodoItem item;
  list.buildList(RAWLIST1);
  item.buildItem(ITEM1);
  EXPECT_TRUE(list[1] == item);
}

TEST(TodoListTest, TestListSize) {
  RTT::TodoList list;
  list.buildList(RAWLIST1);
  EXPECT_EQ(list.size(), 4);
}

TEST(TodoListTest, TestAddItem) {
  RTT::TodoList list;
  RTT::TodoItem item;
  list.buildList(RAWLIST1);
  item.buildItem(" Extra item ");
  list.addItem(item);
  EXPECT_EQ(list.size(), 5);
  EXPECT_TRUE(list.hasItem(item));
}

TEST(TodoListTest, TestListHasItem) {
  RTT::TodoList list;
  RTT::TodoItem item1;
  RTT::TodoItem item2("Hejsan");
  item1.buildItem(ITEM1);
  list.buildList(RAWLIST1);
  EXPECT_TRUE(list.hasItem(item1));
  EXPECT_FALSE(list.hasItem(item2));
}

TEST(TodoListTest, TestRemoveExistingItem) {
  RTT::TodoList list;
  RTT::TodoItem item;
  item.buildItem(ITEM1);
  list.buildList(RAWLIST1);
  list.removeItem(item);
  EXPECT_EQ(list.size(), 3);
  EXPECT_FALSE(list.hasItem(item));
}

TEST(TodoListTest, TestRemoveNonExistingItem) {
  RTT::TodoList list;
  RTT::TodoItem item("Non-existing item");
  list.buildList(RAWLIST1);
  list.removeItem(item);
  EXPECT_EQ(list.size(), 4);
}

TEST(TodoListTest, TestEqualLists) {
  RTT::TodoList list1;
  RTT::TodoList list2;
  list1.buildList(RAWLIST_SAME1);
  list2.buildList(RAWLIST_SAME2);
  EXPECT_TRUE(list1 == list2);
}

TEST(TodoListTest, TestNonEqualLists) {
  RTT::TodoList list1;
  RTT::TodoList list2;
  list1.buildList(RAWLIST_SAME1);
  list2.buildList(RAWLIST_WRONG1);
  EXPECT_FALSE(list1 == list2);
}

TEST(TodoListTest, TestListsOfDifferentSizes) {
  RTT::TodoList list1;
  RTT::TodoList list2;
  RTT::TodoItem item("Extra");
  list1.buildList(RAWLIST_SAME1);
  list2.buildList(RAWLIST_SAME2);
  list2.addItem(item);
  EXPECT_FALSE(list1 == list2);
}

TEST(TodoListTest, TestListsAddingSameItem) {
  RTT::TodoList list1;
  RTT::TodoList list2;
  RTT::TodoItem item("Extra");
  list1.buildList(RAWLIST_SAME1);
  list2.buildList(RAWLIST_SAME2);
  list1.addItem(item);
  list2.addItem(item);
  EXPECT_TRUE(list1 == list2);
}



// TEST(TodoListTest, TestNrOfRemovedItems) {
//   RTT::TodoList list;
//   RTT::TodoItem item;
//   list.buildList(RAWLIST);
//   list.buildList(RAWLIST2);
//   EXPECT_TRUE(list.nrOfRemovedItems() == 1);
// }

// TEST(TodoListTest, TestRemovedItem) {
//   RTT::TodoList list;
//   list.buildList(RAWLIST);
//   list.buildList(RAWLIST2);
//   RTT::TodoItem item;
//   item.buildItem("(A) Handla @Errands");
//   RTT::TodoItem removedItem = list.getRemovedItem(0);
//   EXPECT_TRUE(item == removedItem);
// }
