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
