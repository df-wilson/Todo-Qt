#include "todoitem.h"
#include "ui_todoitem.h"

TodoItem::TodoItem(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::TodoItem)
{
   ui->setupUi(this);
}

TodoItem::~TodoItem()
{
   delete ui;
}

void TodoItem::setDescription(const QString& description)
{
   ui->todoDescriptionLabel->setText(description);
}
