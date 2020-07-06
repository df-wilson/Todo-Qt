#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QSqlDatabase>
#include <QString>

class DbManager
{
public:
   struct TodoItemData
   {
      QString description;
      QString priority;
      QString status;
      QString dueDate;
   };

   DbManager(const QString& path);
   virtual ~DbManager();

   bool addTodoItem(const QString& text, QString& priority, QString& status, QString date);
   std::vector<TodoItemData> activeTodos();
   std::vector<TodoItemData> allTodos();
   bool isOpen() const;

private:
   QSqlDatabase mDb;
};

#endif // DBMANAGER_H
