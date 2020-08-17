#ifndef TODOFRAME_H
#define TODOFRAME_H

/*---------  Program Includes  ----------------*/

#include "dbmanager.h"

/*---------  System Includes  -----------------*/

#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QObject>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>


/*---------  Class Definition  ----------------*/

class TodoFrame : public QObject
{
   Q_OBJECT

public:

   /*---------  Public Methods  ------------------*/

   TodoFrame(const DbManager::TodoItemData &todo);
   virtual ~TodoFrame();

   QFrame* getFrame();
   void setId(unsigned int id);
   void setVisible(bool isVisible);
   void setDescription(QString description);
   void setPriority(QString priority);
   void setStatus(QString status);
   void setDate(QDate& dueAt);

private:

   /*---------  Private Data  --------------------*/

   QFrame* mTodoFrame;
   QVBoxLayout* mTodoFrameLayout;
   QHBoxLayout* mDescriptionLayout;
   QHBoxLayout* mOptionsLayout;
   QHBoxLayout* mDateDueLayout;

   QLabel* mPriorityLabel;
   QLabel* mStatusLabel;
   QLabel* mDueLabel;

   unsigned int mId;
   QPlainTextEdit* mDescription;
   QComboBox* mPriorityComboBox;
   QComboBox* mStatusComboBox;
   QDateEdit* mDateEdit;

   QPushButton* mDeleteButton;

   const QString mPath = "./database/database.sqlite";
   DbManager* mDbManager;


   /*---------  Private Methods  -----------------*/

   int priorityStringToIndex(QString item);
   int statusStringToIndex(QString item);
   void handlePriorityIndexChanged(const QString& value);
   void handleStatusIndexChanged(const QString& value);

private slots:
   void handleDeleteButtonClicked();
};

#endif // TODOFRAME_H
