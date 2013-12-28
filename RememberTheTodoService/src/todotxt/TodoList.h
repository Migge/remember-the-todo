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

    void buildList(QString rawfile);

  private:
    QList<RTT::TodoItem> internalList;

  };  // end class

}  // end namespace

#endif  // TODOLIST_H
