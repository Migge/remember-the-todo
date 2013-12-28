#ifndef TODOITEM_H
#define TODOITEM_H

#include <QtCore/QString>

namespace RTT {

  typedef enum {
    None = 0,
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
  } Priority;


  class TodoItem
  {
  public:
    TodoItem(QString action = "");
    bool operator==(const TodoItem &other) const;
    bool operator!=(const TodoItem &other) const;

    void buildItem(QString rawstring);

    void setAction(QString action);
    const QString& getAction() const;

    void setPriority(Priority priority);
    Priority getPriority() const;

    void setContext(QString context);
    const QString& getContext() const;

    void setProject(QString project);
    const QString& getProject() const;

  private:
    QString action;
    Priority priority;
    QString context;
    QString project;

  };  // end class

}  // end namespace


#endif  // TODOITEM_H
