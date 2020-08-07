#ifndef NEWTODODIALOG_H
#define NEWTODODIALOG_H

/*---------  Program Includes  ----------------*/

#include "dbmanager.h"

/*---------  System Includes  -----------------*/

#include <QDialog>


namespace Ui {
class NewTodoDialog;
}

/*---------  Class Definition  ----------------*/

class NewTodoDialog : public QDialog
{
   Q_OBJECT

public:

   /*---------  Public Methods  ------------------*/

   explicit NewTodoDialog(QWidget *parent = nullptr);
   ~NewTodoDialog();

private slots:

   /*---------  Private Methods  -----------------*/

   void on_addButton_clicked();
   void on_doneButton_clicked();


private:

   /*---------  Private Data  --------------------*/

   Ui::NewTodoDialog *ui;
   const QString mPath = "./database/database.sqlite";
   DbManager* mDbManager;
};

#endif // NEWTODODIALOG_H
