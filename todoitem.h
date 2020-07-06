#ifndef TODOITEM_H
#define TODOITEM_H

#include <QWidget>

namespace Ui {
class TodoItem;
}

class TodoItem : public QWidget
{
   Q_OBJECT

public:
   explicit TodoItem(QWidget *parent = nullptr);
   ~TodoItem();

private:
   Ui::TodoItem *ui;
};

#endif // TODOITEM_H
