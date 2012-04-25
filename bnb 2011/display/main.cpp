#include<QtGui>
#include<QtCore>
#include<QApplication>
#include"dis.h"
int main(int argc,char *argv[])
{
   QApplication app(argc,argv);
   Dis d;
    d.show();
     return d.exec();
 }
