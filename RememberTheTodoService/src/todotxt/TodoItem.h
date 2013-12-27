#ifndef TODOITEM_H
#define TODOITEM_H

#include "types.h"

//#include <string>
#include <QtCore/QString>

class TodoItem
{
 public:
  TodoItem(QString action = "");

  void buildItem(QString rawstring);

  void setAction(QString action);
  const QString& getAction();

  void setPriority(QString priority);
  RTT::Priority getPriority();

  void setContext(QString context);
  const QString& getContext();

  void setProject(QString project);
  const QString& getProject();

 private:
  QString action;
  RTT::Priority priority;
  QString context;
  QString project;

};  // end class


#endif  // TODOITEM_H
