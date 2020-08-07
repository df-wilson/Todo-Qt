/*---------  Program Includes  ----------------*/

#include "mainwindow.h"

/*---------  System Includes   ----------------*/

#include <QApplication>


/*---------  Public Methods    ----------------*/

/*---------------------------------------------------------------------------
*/
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   w.show();
   return a.exec();
}
