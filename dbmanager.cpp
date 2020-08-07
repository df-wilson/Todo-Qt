/*---------  Program Includes  ----------------*/

#include "dbmanager.h"

/*---------  System Includes   ----------------*/

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <vector>


/*---------  Public Methods    ----------------*/

/*---------------------------------------------------------------------------
*/
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

/*---------------------------------------------------------------------------
*/
DbManager::~DbManager()
{
   if (mDb.isOpen())
   {
      mDb.close();
   }
}

/*---------------------------------------------------------------------------
*/
bool DbManager::addTodoItem(const QString &text, QString &priority, QString &status, QString date)
{
   bool success = false;

   QSqlQuery query;
   query.prepare("INSERT INTO todos (description, priority, status, due_at, created_at, updated_at) VALUES (:description, :priority, :status, :due_at, DateTime('now'), DateTime('now'))");
   query.bindValue(":description", text);
   query.bindValue(":priority", priority);
   query.bindValue(":status", status);
   query.bindValue(":due_at", date);

   if(query.exec())
   {
      success = true;
   }
   else
   {
      QString error = query.lastError().text();
      qDebug() << "addTodo error:"
               << query.lastError();
   }

   return success;
}

/*---------------------------------------------------------------------------
*/
std::vector<DbManager::TodoItemData> DbManager::activeTodos()
{
   std::vector<DbManager::TodoItemData> todos;

   QSqlQuery query("SELECT * FROM todos WHERE status = 'In Progress' OR status = 'Not Started'");
   int idId = query.record().indexOf("id");
   int idDescription = query.record().indexOf("description");
   int idDueAt = query.record().indexOf("due_at");
   int idPriority = query.record().indexOf("priority");
   int idStatus = query.record().indexOf("status");

   while(query.next())
   {
      DbManager::TodoItemData data;
      data.id = query.value(idId).toUInt();
      data.description = query.value(idDescription).toString();
      data.dueDate = query.value(idDueAt).toString();
      data.priority = query.value(idPriority).toString();
      data.status = query.value(idStatus).toString();

      todos.push_back(data);
   }

   return todos;
}

/*---------------------------------------------------------------------------
*/
std::vector<DbManager::TodoItemData> DbManager::allTodos()
{
   std::vector<DbManager::TodoItemData> todos;

   QSqlQuery query("SELECT * FROM todos");
   int idId = query.record().indexOf("id");
   int idDescription = query.record().indexOf("description");
   int idDueAt = query.record().indexOf("due_at");
   int idPriority = query.record().indexOf("priority");
   int idStatus = query.record().indexOf("status");

   while(query.next())
   {
      DbManager::TodoItemData data;
      data.id = query.value(idId).toUInt();
      data.description = query.value(idDescription).toString();
      data.dueDate = query.value(idDueAt).toString();
      data.priority = query.value(idPriority).toString();
      data.status = query.value(idStatus).toString();

      todos.push_back(data);
   }

   return todos;
}

/*---------------------------------------------------------------------------
*/
bool DbManager::deleteTodo(int todoId)
{
   bool success = false;

   QSqlQuery query;
   query.prepare("DELETE FROM todos WHERE id = :id");
   query.bindValue(":id", todoId);

   if(query.exec())
   {
      success = true;
   }
   else
   {
      QString error = query.lastError().text();
      qDebug() << "updatePriority error:"
               << error;
   }

   return success;
}

/*---------------------------------------------------------------------------
*/
bool DbManager::updatePriority(int todoId, const QString &priority)
{
   bool success = false;

   QSqlQuery query;
   query.prepare("UPDATE todos SET priority = :priority WHERE id = :todoId");
   query.bindValue(":priority", priority);
   query.bindValue(":todoId", todoId);

   if(query.exec())
   {
      success = true;
   }
   else
   {
      QString error = query.lastError().text();
      qDebug() << "updatePriority error:"
               << query.lastError();
   }

   return success;
}

/*---------------------------------------------------------------------------
*/
bool DbManager::updateStatus(int todoId, const QString &status)
{
   bool success = false;

   QSqlQuery query;
   query.prepare("UPDATE todos SET status = :status WHERE id = :todoId");
   query.bindValue(":status", status);
   query.bindValue(":todoId", todoId);

   if(query.exec())
   {
      success = true;
   }
   else
   {
      QString error = query.lastError().text();
      qDebug() << "updateStatus error:"
               << query.lastError();
   }

   return success;
}

/*---------------------------------------------------------------------------
*/
bool DbManager::isOpen() const
{
      return mDb.isOpen();
}
