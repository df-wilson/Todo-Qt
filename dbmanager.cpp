#include "dbmanager.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <vector>

DbManager::DbManager(const QString &path)
{
   mDb = QSqlDatabase::addDatabase("QSQLITE");
   mDb.setDatabaseName(path);

   if (mDb.open())
   {
      qDebug() << "Database: connection ok";
   }
   else
   {
      qDebug() << "Error: connection with database failed";
   }
}

DbManager::~DbManager()
{
   if (mDb.isOpen())
   {
      mDb.close();
   }
}

bool DbManager::addTodoItem(const QString &text, QString &priority, QString &status, QString date)
{
   bool success = false;

   QSqlQuery query;
   query.prepare("INSERT INTO todos (description, priority, status, due_at) VALUES (:text, :priority, :status, :date");
   query.bindValue(":description,", text);
   query.bindValue(":priority,", priority);
   query.bindValue(":status,", status);
   query.bindValue(":due_at,", date);

   if(query.exec())
   {
      success = true;
   }
   else
   {
      qDebug() << "addTodo error:"
               << query.lastError();
   }

   return success;
}

std::vector<DbManager::TodoItemData> DbManager::activeTodos()
{
   std::vector<DbManager::TodoItemData> todos;

   QSqlQuery query("SELECT * FROM todos WHERE status = 'In Progress' OR status = 'Not Started'");
   int idDescription = query.record().indexOf("description");
   int idDueAt = query.record().indexOf("due_at");
   int idPriority = query.record().indexOf("priority");
   int idStatus = query.record().indexOf("status");

   while(query.next())
   {
      DbManager::TodoItemData data;
      data.description = query.value(idDescription).toString();
      data.dueDate = query.value(idDueAt).toString();
      data.priority = query.value(idPriority).toString();
      data.status = query.value(idStatus).toString();

      todos.push_back(data);
   }

   return todos;
}

std::vector<DbManager::TodoItemData> DbManager::allTodos()
{
   std::vector<DbManager::TodoItemData> todos;

   QSqlQuery query("SELECT * FROM todos");
   int idDescription = query.record().indexOf("description");
   int idDueAt = query.record().indexOf("due_at");
   int idPriority = query.record().indexOf("priority");
   int idStatus = query.record().indexOf("status");

   while(query.next())
   {
      DbManager::TodoItemData data;
      data.description = query.value(idDescription).toString();
      data.dueDate = query.value(idDueAt).toString();
      data.priority = query.value(idPriority).toString();
      data.status = query.value(idStatus).toString();

      todos.push_back(data);
   }

   return todos;
}

bool DbManager::isOpen() const
{
      return mDb.isOpen();
}
