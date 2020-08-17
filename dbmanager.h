#ifndef DBMANAGER_H
#define DBMANAGER_H

/*---------  System Includes  -----------------*/
#include <QDebug>
#include <QSqlDatabase>
#include <QString>

/*---------  Class Definition  ----------------*/

class DbManager
{
public:
   struct TodoItemData
   {
      unsigned int id;
      QString description;
      QString priority;
      QString status;
      QString dueDate;
   };

   /*---------  Public Methods  ------------------*/

   DbManager(const QString& path);
   virtual ~DbManager();

   bool addTodoItem(const QString& text, QString& priority, QString& status, QString date);
   std::vector<TodoItemData> activeTodos();
   std::vector<TodoItemData> allTodos();
   bool deleteTodo(int todoId);
   bool updateDueDate(int todoId, const QString& dueAt);
   bool updatePriority(int todoId, const QString& priority);
   bool updateStatus(int todoId, const QString& status);

   bool isOpen() const;

private:

   /*---------  Private Data  --------------------*/
   QSqlDatabase mDb;
};

#endif // DBMANAGER_H
