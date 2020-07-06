#include <QString>

#include "newtododialog.h"
#include "ui_newtododialog.h"

NewTodoDialog::NewTodoDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::NewTodoDialog)
{
   ui->setupUi(this);
}

NewTodoDialog::~NewTodoDialog()
{
   delete ui;
}

void NewTodoDialog::on_addButton_clicked()
{
    QString todoText = ui->plainTextEdit->document()->toPlainText();
    QString priority = ui->priorityComboBox->currentText();
    QString status = ui->statusComboBox->currentText();
    QString dueDate = ui->dueDateEdit->text();

    return;
}

void NewTodoDialog::on_doneButton_clicked()
{
   accept();
}
