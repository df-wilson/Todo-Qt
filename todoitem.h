#ifndef TODOITEM_H
#define TODOITEM_H

#include <QString>
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

   void setDescription(const QString& description);

private:
   Ui::TodoItem *ui;
};

#endif // TODOITEM_H
