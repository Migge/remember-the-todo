#include "TodoList.h"

#include <QtCore/QRegExp>
#include <QtCore/QStringList>


RTT::TodoList::TodoList()
{
}

RTT::TodoItem RTT::TodoList::operator[](std::size_t idx)
{
  if (idx >= internalList.size()) {
    RTT::TodoItem emptyItem;
    return emptyItem;
  }
  return internalList[idx];
}

int RTT::TodoList::size()
{
  return internalList.size();
}

void RTT::TodoList::buildList(QString rawfile)
{
  QList<RTT::TodoItem> newList;
  QStringList stringList = 
    rawfile.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

  for (int i=0; i<stringList.size(); i++) {
    RTT::TodoItem item;
    item.buildItem(stringList[i]);
    newList << item;
    internalList.removeOne(item);
  }
  removedList = internalList;
  internalList = newList;
}

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
