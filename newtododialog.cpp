#include <QString>

#include "newtododialog.h"
#include "ui_newtododialog.h"

#include "dbmanager.h"

NewTodoDialog::NewTodoDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::NewTodoDialog)
{
   ui->setupUi(this);
   mDbManager = new DbManager(mPath);
}

NewTodoDialog::~NewTodoDialog()
{
   delete ui;
   delete mDbManager;
}

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
}

void NewTodoDialog::on_doneButton_clicked()
{
   accept();
}
