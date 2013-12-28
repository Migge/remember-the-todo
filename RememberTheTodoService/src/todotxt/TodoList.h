#ifndef TODOLIST_H
#define TODOLIST_H

#include "TodoItem.h"

#include <QtCore/QList>
#include <QtCore/QString>


namespace RTT {

  class TodoList
  {
  public:
    TodoList();
    TodoItem operator[](std::size_t idx);
    int size();

    void buildList(QString rawfile);

    int nrOfRemovedItems();
    TodoItem getRemovedItem(std::size_t idx);

  private:
    QList<TodoItem> internalList;
    QList<TodoItem> removedList;

  };  // end class

}  // end namespace

#endif  // TODOLIST_H
