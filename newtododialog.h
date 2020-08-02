#ifndef NEWTODODIALOG_H
#define NEWTODODIALOG_H

#include "dbmanager.h"

#include <QDialog>

namespace Ui {
class NewTodoDialog;
}

class NewTodoDialog : public QDialog
{
   Q_OBJECT

public:
   explicit NewTodoDialog(QWidget *parent = nullptr);
   ~NewTodoDialog();

private slots:
   void on_addButton_clicked();
   void on_doneButton_clicked();

private:
   Ui::NewTodoDialog *ui;
   const QString mPath = "./database/database.sqlite";
   DbManager* mDbManager;
};

#endif // NEWTODODIALOG_H
