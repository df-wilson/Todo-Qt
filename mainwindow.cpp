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
   if(ui)
   {
      delete ui;
      ui = nullptr;
   }

   if(mScrollArea)
   {
      mScrollArea->takeWidget();
      delete mScrollArea;
      mScrollArea = nullptr;
   }

   if(mMainFrame)
   {
      delete mMainFrame;
      mMainFrame = nullptr;
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
    dialog.exec();
}

void MainWindow::on_showDone_stateChanged(int arg1)
{

}

void MainWindow::showActiveTodos()
{

}

void MainWindow::showAllTodos()
{
   std::vector<DbManager::TodoItemData> todos;

   if(mDbManager->isOpen())
   {
      todos = mDbManager->allTodos();
   }
   else
   {
      qDebug() << "Error opening database.";
   }

   drawSelectedTodos(todos);
}

void MainWindow::drawSelectedTodos(std::vector<DbManager::TodoItemData>& todos)
{

   for (auto& todo : todos)
   {
       QFrame* todoFrame = new QFrame();
       QPlainTextEdit* description = new QPlainTextEdit(todo.description);
       description->setReadOnly(true);

       QLabel* priorityLabel = new QLabel("Priority:");
       QLabel* statusLabel = new QLabel("Status:");
       QLabel* dueLabel = new QLabel("Due At:");

       // Create todo description
       description->setStyleSheet("background-color: white;");
       description->setStyleSheet("font: 18pt");

       // Create priority combo box
      QComboBox* priorityComboBox = new QComboBox;
      priorityComboBox->addItem("High");
      priorityComboBox->addItem("Medium");
      priorityComboBox->addItem("Low");
      priorityComboBox->setCurrentIndex(priorityStringToIndex(todo.priority));

      // Create priority combo box
      QComboBox* statusComboBox = new QComboBox;
      statusComboBox->addItem("Not Started");
      statusComboBox->addItem("In Progress");
      statusComboBox->addItem("Completed");
      statusComboBox->setCurrentIndex(statusStringToIndex(todo.status));

      // Create date widget
      QDate dueDateAt = QDate::fromString(todo.dueDate, "yyyy-MM-dd");
      QDateEdit* dateEdit = new QDateEdit(dueDateAt);
      QPushButton* deleteButton = new QPushButton("X");
      deleteButton->setStyleSheet("background-color: red");

      // Set up the layout.
       QVBoxLayout* todoFrameLayout = new QVBoxLayout();
       QHBoxLayout* descriptionLayout = new QHBoxLayout();
       QHBoxLayout* optionsLayout = new QHBoxLayout();
       QHBoxLayout* dateDueLayout = new QHBoxLayout();

       todoFrameLayout->addLayout(descriptionLayout);
       todoFrameLayout->addLayout(optionsLayout);
       todoFrameLayout->addLayout(dateDueLayout);

       todoFrame->setLayout(todoFrameLayout);
       todoFrame->setFrameShape(QFrame::Panel);

       descriptionLayout->addWidget(description);

       optionsLayout->addWidget(priorityLabel);
       optionsLayout->addWidget(priorityComboBox);
       optionsLayout->addWidget(statusLabel);
       optionsLayout->addWidget(statusComboBox);
       optionsLayout->addStretch();

       dateDueLayout->addWidget(dueLabel);
       dateDueLayout->addWidget(dateEdit);
       dateDueLayout->addStretch();
       dateDueLayout->addWidget(deleteButton);

       mMainFrame->layout()->addWidget(todoFrame);
   }
}

int MainWindow::priorityStringToIndex(QString item)
{
   int index = 0;

   if(item == "High")
   {
      index = 0;
   }
   else if(item == "Medium")
   {
      index = 1;
   }
   else if(item == "Low")
   {
      index = 2;
   }
   else
   {
      // Error
   }

   return index;
}

int MainWindow::statusStringToIndex(QString item)
{
   int index = 0;

   if(item == "Not Started")
   {
      index = 0;
   }
   else if(item == "In Progress")
   {
      index = 1;
   }
   else if(item == "Completed")
   {
      index = 2;
   }
   else
   {
      // Error
   }

   return index;
}
