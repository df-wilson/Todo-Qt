#include "mainwindow.h"
#include "newtododialog.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"

#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QPlainTextEdit>

#include <iostream>
#include <vector>


MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   // This frame stores all of the todo items
   mMainFrame = new QFrame();
   mMainFrame->setLayout(new QVBoxLayout());

   mScrollArea = new QScrollArea;
   mScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
   mScrollArea->setMinimumHeight(600);
   mScrollArea->setMaximumHeight(5000);
   mScrollArea->setWidgetResizable(true);
   mScrollArea->setWidget(mMainFrame);
   ui->todoLayout->layout()->addWidget(mScrollArea);

   mDbManager = new DbManager(mPath);

   showAllTodos();
}

MainWindow::~MainWindow()
{
   QLayoutItem *child;
    while ((child = mMainFrame->layout()->takeAt(0)) != 0)
    {
       delete child;
       child = nullptr;
    }

    if(mMainFrame->layout())
    {
       delete mMainFrame->layout();
    }

   mTodoFrames.clear();

   if(mMainFrame)
   {
      delete mMainFrame;
      mMainFrame = nullptr;
   }

   if(mScrollArea)
   {
      mScrollArea->takeWidget();
      delete mScrollArea;
      mScrollArea = nullptr;
   }

   if(ui)
   {
      delete ui;
      ui = nullptr;
   }

   if(mDbManager)
   {
      delete mDbManager;
      mDbManager = nullptr;
   }
}


void MainWindow::on_newButton_clicked()
{
    NewTodoDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        std::cout << "In on_newButton_clicked" << std::endl;
        showAllTodos();
    }
}

void MainWindow::on_showDone_stateChanged(int arg1)
{

}

QFrame *MainWindow::createNewTodoFrame(const DbManager::TodoItemData &todo)
{
   mTodoFrames.push_back(std::unique_ptr<TodoFrame>(new TodoFrame(todo)));

   return mTodoFrames.back()->getFrame();
}

void MainWindow::showActiveTodos()
{

}

void MainWindow::showAllTodos()
{
   std::vector<DbManager::TodoItemData> todos;

   if(mDbManager->isOpen())
   {
   std::cout << "In showAllTodos. Database open.";
   }
   else
   {
      std::cout << "In showAllTodos. Error opening database.";
   }

   todos = mDbManager->allTodos();
   drawSelectedTodos(todos);
}

/*---------------------------------------------------------------------------
*/
void MainWindow::drawSelectedTodos(std::vector<DbManager::TodoItemData>& todos)
{
   size_t numTodoFrames = mMainFrame->layout()->count();
   QWidget* todoFrame = nullptr;

   size_t todoCount = 0;
   for (auto& todo : todos)
   {
      if(numTodoFrames <= todoCount)
      {
          todoFrame = createNewTodoFrame(todo);
          mMainFrame->layout()->addWidget(todoFrame);
      }
      else
      {
         mTodoFrames[todoCount]->setDescription(todo.description);
         mTodoFrames[todoCount]->setPriority(todo.priority);
         mTodoFrames[todoCount]->setStatus(todo.status);
         mTodoFrames[todoCount]->setVisible(true);
      }

      todoCount++;
   }

   for(unsigned int i = todoCount; i < numTodoFrames; ++i)
   {
      mTodoFrames[i]->setVisible(false);
   }
}
