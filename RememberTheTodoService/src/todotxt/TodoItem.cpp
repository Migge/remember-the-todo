#include "TodoItem.h"

#include <QtCore/QRegExp>
#include <QtCore/QStringList>

TodoItem::TodoItem(QString action)
{
  this->action = action;
  this->priority = RTT::None;
  this->context = "";
  this->project = "";
}

void TodoItem::buildItem(QString rawstring)
{
  //"\([ABC]\)"
  QRegExp prioRegExp("^\\([ABC]\\)");
  QRegExp contextRegExp("@\\w+");
  QRegExp projectRegExp("\\+\\w+");
  QString str = rawstring.simplified();
  if (str.contains(prioRegExp)) {
    QString cap = prioRegExp.capturedTexts()[0];
    if ( cap == "(B)" ) {
      this->priority = RTT::B;
    }
    str.remove(cap);
  }
  if (str.contains(contextRegExp)) {
    QString cap = contextRegExp.capturedTexts()[0];
    this->context = cap;
    str.remove(cap);
  }
  if (str.contains(projectRegExp)) {
    QString cap = projectRegExp.capturedTexts()[0];
    this->project = cap;
    str.remove(cap);
  }
  this->action = str.simplified();
}

void TodoItem::setAction(QString action)
{
  this->action = action;
}
const QString& TodoItem::getAction()
{
  return this->action;
}

void TodoItem::setPriority(RTT::Priority priority)
{
  this->priority = priority;
}
RTT::Priority TodoItem::getPriority() {
  return this->priority;
}

void TodoItem::setContext(QString context)
{
  this->context = context;
}
const QString& TodoItem::getContext()
{
  return this->context;
}

void TodoItem::setProject(QString project)
{
  this->project = project;
}
const QString& TodoItem::getProject()
{
  return this->project;
}
