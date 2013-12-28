#include <gtest/gtest.h>
#include "../TodoList.h"

#define RAWLIST "Äta frukost\n(A) Handla @Errands\nPryla Björk +Viktigt"

TEST(TodoListTest, TestBuildNewList) {
  RTT::TodoList list;
  RTT::TodoItem item;
  list.buildList(RAWLIST);
  item.buildItem("  (A)  @Errands  Handla ");
  EXPECT_TRUE(list[1] == item);
}

