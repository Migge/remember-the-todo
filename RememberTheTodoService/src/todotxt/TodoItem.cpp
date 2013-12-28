#include "TodoItem.h"

#include <QtCore/QRegExp>
#include <QtCore/QStringList>

RTT::TodoItem::TodoItem(QString action)
{
  this->action = action;
  this->priority = None;
  this->context = "";
  this->project = "";
}

void RTT::TodoItem::buildItem(QString rawstring)
{
  QRegExp prioRegExp("^\\([A-Z]\\)");
  QRegExp contextRegExp("@\\w+");
  QRegExp projectRegExp("\\+\\w+");
  QString str = rawstring.simplified();
  if (str.contains(prioRegExp)) {
    QString cap = prioRegExp.capturedTexts()[0];
    setPriority((RTT::Priority)((int)RTT::A + (int)(cap[1].toLatin1() - 'A')));
    str.remove(cap);
  }
  if (str.contains(contextRegExp)) {
    QString cap = contextRegExp.capturedTexts()[0];
    setContext(cap);
    str.remove(cap);
  }
  if (str.contains(projectRegExp)) {
    QString cap = projectRegExp.capturedTexts()[0];
    setProject(cap);
    str.remove(cap);
  }
  this->action = str.simplified();
}

void RTT::TodoItem::setAction(QString action)
{
  this->action = action;
}
const QString& RTT::TodoItem::getAction() const
{
  return this->action;
}

void RTT::TodoItem::setPriority(RTT::Priority priority)
{
  this->priority = priority;
}
RTT::Priority RTT::TodoItem::getPriority() const
{
  return this->priority;
}

void RTT::TodoItem::setContext(QString context)
{
  this->context = context;
}
const QString& RTT::TodoItem::getContext() const
{
  return this->context;
}

void RTT::TodoItem::setProject(QString project)
{
  this->project = project;
}
const QString& RTT::TodoItem::getProject() const
{
  return this->project;
}

bool RTT::TodoItem::operator==(const RTT::TodoItem &other) const
{
  return
    getProject() == other.getProject() &&
    getContext() == other.getContext() &&
    getPriority() == other.getPriority() &&
    getAction() == other.getAction();
}

bool RTT::TodoItem::operator!=(const RTT::TodoItem &other) const
{
  return !(*this == other);
}
