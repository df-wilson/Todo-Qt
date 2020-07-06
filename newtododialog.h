#ifndef NEWTODODIALOG_H
#define NEWTODODIALOG_H

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

private:
   Ui::NewTodoDialog *ui;
};

#endif // NEWTODODIALOG_H
