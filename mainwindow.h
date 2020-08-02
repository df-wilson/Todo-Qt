#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include "todoframe.h"

#include <QFrame>
#include <QMainWindow>
#include <QScrollArea>

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private slots:
   void on_newButton_clicked();
   void on_showDone_stateChanged(int arg1);

private:
   Ui::MainWindow *ui;
   QScrollArea* mScrollArea;
   QFrame* mMainFrame;

   const QString mPath = "./database/database.sqlite";
   DbManager *mDbManager;

   std::vector<std::unique_ptr<TodoFrame>> mTodoFrames;

   QFrame *createNewTodoFrame(const DbManager::TodoItemData& data);
   void showActiveTodos();
   void showAllTodos();
   void drawSelectedTodos(std::vector<DbManager::TodoItemData>& todos);
};
#endif // MAINWINDOW_H
