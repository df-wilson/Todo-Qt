#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*---------  Program Includes  ----------------*/

#include "dbmanager.h"
#include "todoframe.h"

/*---------  System Includes  -----------------*/

#include <QFrame>
#include <QMainWindow>
#include <QScrollArea>

#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*---------  Class Definition  ----------------*/

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:

   /*---------  Public Methods  ------------------*/

   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private slots:

   /*---------  Private Methods  -----------------*/

   void on_newButton_clicked();
   void on_showDone_stateChanged(int state);

private:

   /*---------  Private Data  --------------------*/

   const QString mPath = "./database/database.sqlite";

   Ui::MainWindow *ui;
   QScrollArea* mScrollArea;
   QFrame* mMainFrame;
   DbManager *mDbManager;

   std::vector<std::unique_ptr<TodoFrame>> mTodoFrames;


   /*---------  Private Methods  -----------------*/

   QFrame *createNewTodoFrame(const DbManager::TodoItemData& data);
   void showActiveTodos();
   void showAllTodos();
   void drawSelectedTodos(std::vector<DbManager::TodoItemData>& todos);
};

#endif // MAINWINDOW_H
