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

void RTT::TodoList::buildList(QString rawfile)
{
  QStringList stringList = 
    rawfile.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

  for (int i=0; i<stringList.size(); i++) {
    RTT::TodoItem item;
    item.buildItem(stringList[i]);
    internalList.append(item);
  }
}
