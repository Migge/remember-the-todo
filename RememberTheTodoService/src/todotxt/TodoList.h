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
    bool operator==(const TodoList &other) const;
    int size() const;

    void buildList(const QString rawfile);
    void addItem(const TodoItem item);
    bool hasItem(const TodoItem item) const;
    void removeItem(const TodoItem item);

    //int nrOfRemovedItems();
    //TodoItem getRemovedItem(std::size_t idx);

  private:
    QList<TodoItem> todoList;
    //QList<TodoItem> removedList;

  };  // end class TodoList

}  // end namespace RTT

#endif  // TODOLIST_H
