/*---------  Program Includes  ----------------*/

#include "dbmanager.h"
#include "newtododialog.h"
#include "ui_newtododialog.h"

/*---------  System Includes   ----------------*/

#include <QString>


/*---------  Public Methods    ----------------*/

/*---------------------------------------------------------------------------
*/
NewTodoDialog::NewTodoDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::NewTodoDialog)
{
   ui->setupUi(this);
   ui->dueDateEdit->setDate(QDate::currentDate());

   mDbManager = new DbManager(mPath);
}

/*---------------------------------------------------------------------------
*/
NewTodoDialog::~NewTodoDialog()
{
   delete ui;
   delete mDbManager;
}


/*---------  Private Methods  -----------------*/

/*---------------------------------------------------------------------------
*/
void NewTodoDialog::on_addButton_clicked()
{
   QString todoText = ui->plainTextEdit->document()->toPlainText();
   QString priority = ui->priorityComboBox->currentText();
   QString status = ui->statusComboBox->currentText();
   QString dueDate = ui->dueDateEdit->text();

   mDbManager->addTodoItem(todoText, priority, status, dueDate);

   // Reset fields for next todo
   ui->plainTextEdit->document()->setPlainText("");
   ui->priorityComboBox->setCurrentIndex(0);
   ui->statusComboBox->setCurrentIndex(0);
   ui->dueDateEdit->setDate(QDate::currentDate());
}

/*---------------------------------------------------------------------------
*/
void NewTodoDialog::on_doneButton_clicked()
{
   accept();
}
