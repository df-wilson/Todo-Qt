/*---------  Program Includes  ----------------*/

#include "todoframe.h"


/*---------  System Includes   ----------------*/

#include <QMessageBox>
#include <QObject>

/*---------  Public Methods    ----------------*/

/*---------------------------------------------------------------------------
*/
TodoFrame::TodoFrame(const DbManager::TodoItemData &todo)
{
   mTodoFrame = new QFrame();

   mId = todo.id;

   // Create todo description
   mDescription = new QPlainTextEdit(todo.description);
   mDescription->setReadOnly(true);
   mDescription->setStyleSheet("background-color: white;");
   mDescription->setStyleSheet("font: 18pt");

   mPriorityLabel = new QLabel("Priority:");
   mStatusLabel = new QLabel("Status:");
   mDueLabel = new QLabel("Due At:");

   // Create priority combo box
  mPriorityComboBox = new QComboBox;
  mPriorityComboBox->addItem("High");
  mPriorityComboBox->addItem("Medium");
  mPriorityComboBox->addItem("Low");
  mPriorityComboBox->setCurrentIndex(priorityStringToIndex(todo.priority));
  connect(mPriorityComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), [=](const QString& index){ handlePriorityIndexChanged(index); });

  // Create status combo box
  mStatusComboBox = new QComboBox;
  mStatusComboBox->addItem("Not Started");
  mStatusComboBox->addItem("In Progress");
  mStatusComboBox->addItem("Completed");
  mStatusComboBox->setCurrentIndex(statusStringToIndex(todo.status));
  connect(mStatusComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), [=](const QString& index){ handleStatusIndexChanged(index); });

  // Create date widget
  QDate dueDateAt = QDate::fromString(todo.dueDate, "yyyy-MM-dd");
  mDateEdit = new QDateEdit(dueDateAt);
  mDeleteButton = new QPushButton("X");
  mDeleteButton->setStyleSheet("background-color: red");
  connect(mDeleteButton, SIGNAL (clicked()), this, SLOT (handleDeleteButtonClicked()));

  // Set up the layout.
   mTodoFrameLayout = new QVBoxLayout();
   mDescriptionLayout = new QHBoxLayout();
   mOptionsLayout = new QHBoxLayout();
   mDateDueLayout = new QHBoxLayout();

   mTodoFrameLayout->addLayout(mDescriptionLayout);
   mTodoFrameLayout->addLayout(mOptionsLayout);
   mTodoFrameLayout->addLayout(mDateDueLayout);

   mTodoFrame->setLayout(mTodoFrameLayout);
   mTodoFrame->setFrameShape(QFrame::Panel);

   mDescriptionLayout->addWidget(mDescription);

   mOptionsLayout->addWidget(mPriorityLabel);
   mOptionsLayout->addWidget(mPriorityComboBox);
   mOptionsLayout->addWidget(mStatusLabel);
   mOptionsLayout->addWidget(mStatusComboBox);
   mOptionsLayout->addStretch();

   mDateDueLayout->addWidget(mDueLabel);
   mDateDueLayout->addWidget(mDateEdit);
   mDateDueLayout->addStretch();
   mDateDueLayout->addWidget(mDeleteButton);

   mDbManager = new DbManager(mPath);
}

/*---------------------------------------------------------------------------
*/
TodoFrame::~TodoFrame()
{
   delete mDescription;

   delete mPriorityLabel;
   delete mPriorityComboBox;

   delete mStatusLabel;
   delete mStatusComboBox;

   delete mDueLabel;
   delete mDateEdit;

   delete mDeleteButton;

   delete mDescriptionLayout;
   delete mOptionsLayout;
   delete mDateDueLayout;
   delete mTodoFrameLayout;

   delete mTodoFrame;

   delete mDbManager;
}

/*---------------------------------------------------------------------------
*/
QFrame* TodoFrame::getFrame()
{
   return mTodoFrame;
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::setId(unsigned int id)
{
   mId = id;
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::setVisible(bool isVisible)
{
  mTodoFrame->setVisible(isVisible);
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::setDescription(QString description)
{
   mDescription->setPlainText(description);
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::setPriority(QString priority)
{
   mPriorityComboBox->setCurrentIndex(priorityStringToIndex(priority));
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::setStatus(QString status)
{
   mStatusComboBox->setCurrentIndex(statusStringToIndex(status));
}


/*---------  Private Methods  -----------------*/

/*---------------------------------------------------------------------------
*/
void TodoFrame::handleDeleteButtonClicked()
{
   QMessageBox msgBox;
   msgBox.setText("Button clicked.");
   msgBox.exec();
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::handlePriorityIndexChanged(const QString &value)
{
   mDbManager->updatePriority(mId, value);
}

/*---------------------------------------------------------------------------
*/
void TodoFrame::handleStatusIndexChanged(const QString &value)
{
   mDbManager->updateStatus(mId, value);
}

/*---------------------------------------------------------------------------
*/
int TodoFrame::priorityStringToIndex(QString item)
{
   int index = 0;

   if(item == "High")
   {
      index = 0;
   }
   else if(item == "Medium")
   {
      index = 1;
   }
   else if(item == "Low")
   {
      index = 2;
   }
   else
   {
      // Error
   }

   return index;
}

/*---------------------------------------------------------------------------
*/
int TodoFrame::statusStringToIndex(QString item)
{
   int index = 0;

   if(item == "Not Started")
   {
      index = 0;
   }
   else if(item == "In Progress")
   {
      index = 1;
   }
   else if(item == "Completed")
   {
      index = 2;
   }
   else
   {
      // Error
   }

   return index;
}
