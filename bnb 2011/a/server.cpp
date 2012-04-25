#include "server.h"
#include<stdio.h>
#include <QtGui>
#include<QtSql>
#include<QDialog>
#include <iostream>
#include<string.h>
using namespace std;




bool Server::createConnection()
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
Server::Server(QWidget *parent)
     : QDialog(parent)
{
 
  status = new QLabel("results r out !!!!!!!!!!! ");
  ph     = new QLabel("     ");
  createConnection(); 
 
  QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(status, 0, 0);
   mainLayout->addWidget(ph , 3, 0);
  setLayout(mainLayout);

     setWindowTitle(tr("result"));
read();

}


void Server::read()
{

int mv[6],i=0;
//mv
QSqlQuery query;
query.prepare("select mv from c");
//query.bindValue(":c_cid",c_cid);
//query.bindValue(":c_s",c_s);
query.exec();

while (query.next()) {
mv[i++]= query.value(0).toInt();
}
//


int pid=1,c1,c2,c3,c4,c5,c6,amt;

QSqlQuery query1;
while(pid<=99)
{
query1.prepare("select * from p where pid=:pid");
query1.bindValue(":pid",pid);
query1.exec();


while (query1.next()) {
amt= query1.value(1).toInt();
c1= query1.value(2).toInt();
c2= query1.value(3).toInt();
c3= query1.value(4).toInt();
c4= query1.value(5).toInt();
c5= query1.value(6).toInt();
c6= query1.value(7).toInt();
}
int sum=0;

sum=amt+(c1*mv[0]+c2*mv[1]+c3*mv[2]+c4*mv[3]+c5*mv[4]+c6*mv[5]);

	
QSqlQuery query2;

query2.prepare("insert into r values (:pid,:sum)");

query2.bindValue(":sum",sum);
query2.bindValue(":pid",pid);
query2.exec();
qDebug()<<sum;
pid++;
}



}    

