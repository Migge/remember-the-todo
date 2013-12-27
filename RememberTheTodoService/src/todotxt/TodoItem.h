#ifndef TODOITEM_H
#define TODOITEM_H


#include <string>

class TodoItem
{
public:
  TodoItem(std::string action = "");
  ~TodoItem();

  enum Priority {
    A,
    B,
    C,
    None
  };

  void setPriority(TodoItem::Priority priority);
  TodoItem::Priority getPriority();

  void setContext(std::string context);
  const std::string& getContext();

  void setProject(std::string project);
  const std::string& getProject();

private:
  std::string action;
  TodoItem::Priority priority;
  std::string context;
  std::string project;

};  // end class


#endif  // TODOITEM_H
