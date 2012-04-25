#include "server.h"
#include<stdio.h>
#include <QtGui>
#include<QtSql>
#include <QtNetwork>
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
  server = new QTcpServer;
  socket = new QTcpSocket;
  status = new QLabel("Server is ready to read ");
  ph     = new QLabel("     ");
  createConnection(); 
 connect(server, SIGNAL(newConnection()), this, SLOT(acceptconnection()));
//connect(server,SIGNAL(disconnected()),this,SLOT(disconnect()));
  server->listen(QHostAddress::Any, 18888);
  QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(status, 0, 0);
   mainLayout->addWidget(ph , 3, 0);
  setLayout(mainLayout);

     setWindowTitle(tr("Server"));

}
void Server::disconnect()
{
	socket->disconnectFromHost();
}
void Server::acceptconnection()
{ //system("sort database | uniq > database2");
  status->setText("Server is ready to read ");
  socket = server->nextPendingConnection();
//char a[10];
//cin>>a;
//client->write(a,10);
 cout<<"ready";
  connect(socket, SIGNAL(readyRead()),
    this, SLOT(read()));
 // socket->write("hello,world",13);
}
void Server::read()
{

QTime time;
time=QTime::currentTime();
int min,hr,sec;
min=time.minute();
hr=time.hour();
sec=time.second();




QFile f2("./server_log.txt");
f2.open(QIODevice::Append);
QTextStream ot(&f2);


    QDataStream in(socket);
         in.setVersion(QDataStream::Qt_4_0);
 in >> blocksize;
            cout<<blocksize<<endl;
  if (socket->bytesAvailable() < blocksize){cout<<"hi"; return;}
	QString b,s,c,a,n;
        in>>b>>s>>c>>a>>n;
qDebug()<<b<<s<<c<<a<<n;

QString c_cid="c"+c;
int c_s=s.toInt();
int c_b=b.toInt();
int c_a=a.toInt();
int c_n=n.toInt();
int cash=0;
qDebug()<<c_cid<<c_s;
QSqlQuery query;
query.prepare("select amt , "+c_cid+" from p where pid= :c_s");
query.bindValue(":c_cid",c_cid);
query.bindValue(":c_s",c_s);
query.exec();

int cur_samt=0,cur_ssh=0;
int cur_bamt=0,cur_bsh=0;

while (query.next()) {
cur_samt = query.value(0).toInt();
cur_ssh = query.value(1).toInt();
}
//cout<<cur_samt<<cur_ssh<<endl;


QSqlQuery query1;

query1.prepare("select amt , "+c_cid+" from p where pid= :c_b");
query1.bindValue(":c_cid",c_cid);
query1.bindValue(":c_b",c_b);
query1.exec();


while (query1.next()) {
cur_bamt = query1.value(0).toInt();
cur_bsh = query1.value(1).toInt();
}
//cout<<cur_bamt<<cur_bsh<<endl;

cash=c_n*c_a;
int upsellsh=0,upbuysh=0,upsellamt=0,upbuyamt=0;





int int_cid=c.toInt();
int cur_mv=0,cur_esc=0,mv=0,esc=0;
QSqlQuery query4;

query4.prepare("select esc , mv from c where cid=:int_cid");
query4.bindValue(":int_cid",int_cid);
query4.exec();


while (query4.next()) {
cur_mv = query4.value(1).toInt();
cur_esc = query4.value(0).toInt();
}
cout<<endl<<cur_mv<<endl;
cout<<endl<<cur_mv*.25<<endl;

if(!(c_a>cur_mv+(cur_mv*.25) || c_a<cur_mv-(cur_mv*.25)))
{
if ((c_n <= cur_ssh) && (cur_bamt > cash))// && ((cur_mv-(cur_mv*0.25))<c_a && (cur_mv+(cur_mv*0.25))>c_a) )
{
                        upsellsh = cur_ssh - c_n;
                        upbuysh = cur_bsh + c_n;
                        upsellamt = cur_samt + cash;
                        upbuyamt = cur_bamt - cash;


//cout<<upsellsh<<upsellamt<<endl;
//cout<<upbuysh<<upbuyamt<<endl;

QSqlQuery query2;

query2.prepare("update p set amt=:upsellamt,"+c_cid+"=:upsellsh where pid=:c_s");
query2.bindValue(":c_cid",c_cid);
query2.bindValue(":c_s",c_s);
query2.bindValue(":upsellamt",upsellamt);
query2.bindValue(":upsellsh",upsellsh);
query2.exec();


QSqlQuery query3;

query3.prepare("update p set amt=:upbuyamt,"+c_cid+"=:upbuysh where pid=:c_b");
query3.bindValue(":c_cid",c_cid);
query3.bindValue(":c_b",c_b);
query3.bindValue(":upbuyamt",upbuyamt);
query3.bindValue(":upbuysh",upbuysh);
query3.exec();


/*int int_cid=c.toInt();
int cur_mv=0,cur_esc=0,mv=0,esc=0;
QSqlQuery query4;

query4.prepare("select esc , mv from c where cid=:int_cid");
query4.bindValue(":int_cid",int_cid);
query4.exec();


while (query4.next()) {
cur_mv = query4.value(0).toInt();
cur_esc = query4.value(1).toInt();
}*/


cout<<cur_mv<<cur_esc<<endl;


esc = ((cur_mv * cur_esc) + (c_a * c_n)) / (cur_mv + c_a);
mv = ((cur_mv * esc) + (c_a * c_n)) / (esc + c_n);

cout<<mv<<"  "<<esc<<endl;

QSqlQuery query5;

query5.prepare("update c set esc=:esc,mv=:mv where cid=:int_cid");
query5.bindValue(":int_cid",int_cid);
query5.bindValue(":mv",mv);
query5.bindValue(":esc",esc);
query5.exec();


ot<<b<<"|"<<s<<"|"<<c<<"|"<<a<<"|"<<n<<"||"<<upsellamt<<"|"<<upsellsh<<"|"<<upbuyamt<<"|"<<upbuysh<<"||"<<esc<<"|"<<mv<<"|"<<hr<<":"<<":"<<min<<":"<<sec<<"complete\n";

  socket->write("   complete",100);
}
else
{
if(!(c_n<=cur_ssh))
{
char a[100]="not enough shares ",b[10];
int s=0,f=cur_ssh;
while(f>=1)
{
	b[s++]=(f%10)+48;
	f/=10;
}
b[s]='\0';
cout<<endl<<b<<endl;
char temp[100];
strcpy(temp,b);
int i=0,k=strlen(b)-1;
while(temp[i]!='\0')
{
	b[i++]=temp[k--];
}
b[i]='\0';
strcat(a,b);
cout<<a;
//if (!(c_n <= cur_ssh))



ot<<b<<"|"<<s<<"|"<<c<<"|"<<a<<"|"<<n<<"||"<<upsellamt<<"|"<<upsellsh<<"|"<<upbuyamt<<"|"<<upbuysh<<"||"<<esc<<"|"<<mv<<"|"<<hr<<":"<<":"<<min<<":"<<sec<<"no share\n";



	socket->write(a,100);
}
//else if((cur_mv-(cur_mv*.25))>c_a && (cur_mv+(cur_mv*.25))<c_a)
//	socket->write(" ckt error ",100);

else
{

char aa[100]="not enough amt ",ba[10];
int sa=0,fa=cur_bamt;
while(fa>=1)
{
        ba[sa++]=(fa%10)+48;
        fa/=10;
}
ba[sa]='\0';
cout<<endl<<ba<<endl;
char tempa[100];
strcpy(tempa,ba);
int ia=0,ka=strlen(ba)-1;
while(tempa[ia]!='\0')
{
        ba[ia++]=tempa[ka--];
}
ba[ia]='\0';
strcat(aa,ba);
cout<<aa;


ot<<b<<"|"<<s<<"|"<<c<<"|"<<a<<"|"<<n<<"||"<<upsellamt<<"|"<<upsellsh<<"|"<<upbuyamt<<"|"<<upbuysh<<"||"<<esc<<"|"<<mv<<"|"<<hr<<":"<<":"<<min<<":"<<sec<<"no amt\n";

	socket->write(aa,100);
}
}
}
else
{

ot<<b<<"|"<<s<<"|"<<c<<"|"<<a<<"|"<<n<<"||"<<upsellamt<<"|"<<upsellsh<<"|"<<upbuyamt<<"|"<<upbuysh<<"||"<<esc<<"|"<<mv<<"|"<<hr<<":"<<":"<<min<<":"<<sec<<"ckt\n";

	socket->write("ckt error ",100);
}
 socket->disconnectFromHost();
f2.close();
}    

