#include<QtGui>
#include<iostream>
#include<QtSql>
 #include <QString>
#include"client.h"
using namespace std;

bool Client::createConnection()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
db.setHostName("localhost");
db.setDatabaseName("mysql");
db.setUserName("root");
db.setPassword("c");
if (!db.open()) {
QMessageBox::critical(0, QObject::tr("Databaseopen Error"),
db.lastError().text());
return false;
}
return true;
}


 Client::Client(QWidget *parent)
     : QDialog(parent)
 {
  createConnection();
  cid = new QLabel(tr("cid"));
   per = new QLabel(tr("percentage"));


l_per= new QLineEdit;
l_cid = new QLineEdit;

    send = new QPushButton(tr("ok"));

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(cid,1 , 0);
     mainLayout->addWidget(l_cid, 1, 5);
mainLayout->addWidget(per, 2, 0);
     mainLayout->addWidget(l_per, 2, 5);
     
     

    

     mainLayout->addWidget(send,3,2);





     setLayout(mainLayout);
     
     setWindowTitle(tr("divident"));
   connect(send,SIGNAL(clicked()),this,SLOT(read()));
   
   
 }
 
 void Client::read()
  {

int c_id=l_cid->text().toInt(),fv=0;

QSqlQuery query1;
query1.prepare("select fv from c where cid= :c_id");
query1.bindValue(":c_id",c_id);
query1.exec();
while (query1.next()) {
fv= query1.value(0).toInt();
}

int perc=l_per->text().toInt();
int calu= perc*fv/100;
QString c="c"+l_cid->text();
QString cc=QString::number(calu,10);
qDebug()<<cc<<c<<calu<<perc<<fv<<c_id;
QSqlQuery query2;
query2.prepare("update p set amt=amt+("+cc+"*"+c+")");
query2.exec();






  }
