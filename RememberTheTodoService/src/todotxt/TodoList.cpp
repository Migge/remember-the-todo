#include "TodoList.h"

#include <QtCore/QRegExp>
#include <QtCore/QStringList>


RTT::TodoList::TodoList()
{
}

RTT::TodoItem RTT::TodoList::operator[](std::size_t idx)
{
  if ((int)idx >= todoList.size()) {
    RTT::TodoItem emptyItem;
    return emptyItem;
  }
  return todoList[idx];
}

int RTT::TodoList::size() const
{
  return todoList.size();
}

void RTT::TodoList::buildList(QString rawfile)
{
  //QList<RTT::TodoItem> newList;
  todoList.clear();
  
  QStringList stringList = 
    rawfile.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

  for (int i=0; i<stringList.size(); i++) {
    RTT::TodoItem item;
    item.buildItem(stringList[i]);
    todoList << item;
    //internalList.removeOne(item);
  }
  //removedList = internalList;
  //internalList = newList;
}

void RTT::TodoList::addItem(TodoItem item)
{
  todoList << item;
}

bool RTT::TodoList::hasItem(const TodoItem item) const
{
  return todoList.contains(item);
}

void RTT::TodoList::removeItem(const TodoItem item)
{
  todoList.removeOne(item);
}

bool RTT::TodoList::operator==(const RTT::TodoList &other) const
{
  if (this->size() != other.size()) {
    return false;
  }
  for (int i=0; i<this->size(); i++) {
    if (!other.hasItem(todoList[i])) {
      return false;
    }
  }
  return true;
}



/*
int RTT::TodoList::nrOfRemovedItems()
{
  return removedList.size();
}

RTT::TodoItem RTT::TodoList::getRemovedItem(std::size_t idx)
{
  if (idx >= removedList.size()) {
    RTT::TodoItem emptyItem;
    return emptyItem;
  }
  return removedList[idx];
}
*/
