#include "TodoItem.h"

TodoItem::TodoItem(std::string action)
{
  this->action = action;
}

void TodoItem::setPriority(TodoItem::Priority priority)
{
  this->priority = priority;
}
TodoItem::Priority TodoItem::getPriority() {
  return this->priority;
}

void TodoItem::setContext(std::string context)
{
  this->context = context;
}
const std::string& TodoItem::getContext()
{
  return this->context;
}

void TodoItem::setProject(std::string project)
{
  this->project = project;
}
const std::string& TodoItem::getProject()
{
  return this->project;
}
