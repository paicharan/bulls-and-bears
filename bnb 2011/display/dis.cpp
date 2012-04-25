#include<QtGui>
#include<iostream>
#include<QFont>
#include"dis.h"
#include<QVBoxLayout>
using namespace std;
bool Dis::createConnection()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
db.setHostName("localhost");
db.setDatabaseName("mysql");
db.setUserName("root");
db.setPassword("c");
if (!db.open()) {
QMessageBox::critical(0, QObject::tr("Database Error"),
db.lastError().text());
return false;
}
//img->setText("connection ok");
return true;
}
 Dis::Dis(QWidget *parent)
     : QDialog(parent)
 {  
//status = new QLabel(tr("news"));
status = new QLineEdit();
val1 =new QLabel(tr(""));
val2 =new QLabel(tr(""));
val3 =new QLabel(tr(""));
val4 =new QLabel(tr(""));
val5 =new QLabel(tr(""));
val6 =new QLabel(tr(""));
val7 =new QLabel(tr(""));
val8 =new QLabel(tr(""));
val9 =new QLabel(tr(""));

//val1->QFont::setFontSize(20);

status->setFont(QFont("Trebuchet",20,QFont::Bold));

val1->setFont(QFont("Trebuchet",30,QFont::Bold));
val2->setFont(QFont("Trebuchet",30,QFont::Bold));
val3->setFont(QFont("Trebuchet",30,QFont::Bold));
val4->setFont(QFont("Trebuchet",30,QFont::Bold));
val5->setFont(QFont("Trebuchet",30,QFont::Bold));
val6->setFont(QFont("Trebuchet",30,QFont::Bold));
val7->setFont(QFont("Trebuchet",30,QFont::Bold));
val8->setFont(QFont("Trebuchet",30,QFont::Bold));
val9->setFont(QFont("Trebuchet",30,QFont::Bold));


//val7 =new QLabel(tr(""));
//val8 =new QLabel(tr(""));
//val9 =new QLabel(tr(""));
//val10 =new QLabel(tr(""));

val11 =new QLabel("<img src='1.jpeg' />");
val21 =new QLabel("<img src='2.jpeg' />");
val31 =new QLabel("<img src='3.jpeg' />");
val41 =new QLabel("<img src='4.jpeg' />");
val51 =new QLabel("<img src='5.jpeg' />");
val61 =new QLabel("<img src='6.jpeg' />");
val71 =new QLabel("<img src='7.jpeg' />");
val81 =new QLabel("<img src='8.jpeg' />");
val91 =new QLabel("<img src='9.jpeg' />");

//val71 =new QLabel(tr("ICICI_Bank"));
//val81 =new QLabel(tr("ACC"));
//val91 =new QLabel(tr("Infosys"));
//val101 =new QLabel(tr("Reliance"));

QVBoxLayout *vb = new QVBoxLayout;
QHBoxLayout *hb1= new QHBoxLayout;
QHBoxLayout *hb2= new QHBoxLayout;
QHBoxLayout *hb3= new QHBoxLayout;

//     QGridLayout *mainLayout = new QGridLayout;
vb->addWidget(status);
hb1 ->addWidget(val11);
hb1->addWidget(val1);

hb1->addWidget(val21);
hb1->addWidget(val2);


hb1->addWidget(val31);
hb1->addWidget(val3);

vb->addLayout(hb1);

hb2->addWidget(val41);
hb2->addWidget(val4);

hb2->addWidget(val51);
hb2->addWidget(val5);

hb2->addWidget(val61);
hb2->addWidget(val6);

vb->addLayout(hb2);

hb3->addWidget(val71);
hb3->addWidget(val7);

hb3->addWidget(val81);
hb3->addWidget(val8);

hb3->addWidget(val91);
hb3->addWidget(val9);

vb->addLayout(hb3);


 setLayout(vb);
     
     setWindowTitle(tr("BNB"));
   createConnection(); cc=0;
 	QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(display()));
     timer->start(600);



 }
 void Dis::display()
  { 
QString aa;
if (cc==11)cc=1;

cc=1;
QSqlQuery query1;
query1.prepare("select mv from c where cid = :cc");
query1.bindValue(":cc",cc);
query1.exec();
while (query1.next()) {
aa=query1.value(0).toString();
	val1->setText(aa);     
  }

cc++;

QSqlQuery query2;
query2.prepare("select mv from c where cid = :cc");
query2.bindValue(":cc",cc);
query2.exec();
while (query2.next()) {
QString aa=query2.value(0).toString();
        val2->setText(aa);
  }

cc++;
QSqlQuery query3;
query3.prepare("select mv from c where cid = :cc");
query3.bindValue(":cc",cc);
query3.exec();
while (query3.next()) {
QString aa=query3.value(0).toString();
        val3->setText(aa);
  }
cc++;
QSqlQuery query4;
query4.prepare("select mv from c where cid = :cc");
query4.bindValue(":cc",cc);
query4.exec();
while (query4.next()) {
QString aa=query4.value(0).toString();
        val4->setText(aa);
  }

cc++;
QSqlQuery query5;
query5.prepare("select mv from c where cid = :cc");
query5.bindValue(":cc",cc);
query5.exec();
while (query5.next()) {
QString aa=query5.value(0).toString();
        val5->setText(aa);
  }

cc++;
QSqlQuery query6;
query6.prepare("select mv from c where cid = :cc");
query6.bindValue(":cc",cc);
query6.exec();
while (query6.next()) {
QString aa=query6.value(0).toString();
        val6->setText(aa);
  }

cc++;
QSqlQuery query7;
query7.prepare("select mv from c where cid = :cc");
query7.bindValue(":cc",cc);
query7.exec();
while (query7.next()) {
QString aa=query7.value(0).toString();
        val7->setText(aa);
  }

cc++;
QSqlQuery query8;
query8.prepare("select mv from c where cid = :cc");
query8.bindValue(":cc",cc);
query8.exec();
while (query8.next()) {
QString aa=query8.value(0).toString();
        val8->setText(aa);
  }

cc++;
QSqlQuery query9;
query9.prepare("select mv from c where cid = :cc");
query9.bindValue(":cc",cc);
query9.exec();
while (query9.next()) {
QString aa=query9.value(0).toString();
        val9->setText(aa);
  }

/*cc++;
QSqlQuery query10;
query10.prepare("select mv from c where cid = :cc");
query10.bindValue(":cc",cc);
query10.exec();
while (query10.next()) {
QString aa=query10.value(0).toString();
        val10->setText(aa);
  }*/
cc=1;
}
