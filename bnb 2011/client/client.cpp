#include<QtGui>
#include<QTime>
#include<iostream>
#include"client.h"
using namespace std;
 Client::Client(QWidget *parent)
     : QDialog(parent)
 {  bid = new QLabel(tr("buyer_id"));
   sid = new QLabel(tr("seller_id"));
cid = new QLabel(tr("companey_ID "));
amt = new QLabel(tr("amount"));
nos = new QLabel(tr("nos"));
status = new QLabel(tr(""));
status1=new QLabel(tr(""));
    l_bid = new QLineEdit;
l_sid= new QLineEdit;
l_cid = new QLineEdit;
l_amt = new QLineEdit;
l_nos = new QLineEdit;
    send = new QPushButton(tr("send"));
 //   send->setEnabled(false);
    quit = new QPushButton(tr("Quit"));
    tcpSocket = new QTcpSocket(this);
//     start("10.42.43.1", 18888 );
    
     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(bid,1 , 0);
     mainLayout->addWidget(l_bid, 1, 5);
mainLayout->addWidget(sid, 2, 0);
     mainLayout->addWidget(l_sid, 2, 5);
     mainLayout->addWidget(cid,3,0);
     mainLayout->addWidget(l_cid, 3, 5);
mainLayout->addWidget(nos,4,0);
     mainLayout->addWidget(l_nos, 4, 5);
mainLayout->addWidget(amt,5,0);
     mainLayout->addWidget(l_amt, 5, 5);
     mainLayout->addWidget(send,6,0);
//	mainLayout->addWidget(quit,6,4);
mainLayout->addWidget(status, 6,5);
mainLayout->addWidget(status1,7,0);


//send->setEnabled(bid->text().isEmpty());

     setLayout(mainLayout);
     
     setWindowTitle(tr("Client"));
   connect(send,SIGNAL(clicked()),this,SLOT(sendto()));
   connect(quit,SIGNAL(clicked()),this,SLOT(close()));
   connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(read()));
//connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
  //          this, SLOT(displayError(QAbstractSocket::SocketError)));
 //  connect(tcpSocket,SIGNAL(connected()),this,SLOT(sendtoser()));

//connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disable()));
//QFile f2("/home/chinnu/client_log");
//f2.open(QIODevice::Append);
//QDataStream ot(&f2);
//ot.setVersion(QDataStream::Qt_4_0);

//f2.close();
 }
 void Client::start(QString address, quint16 port)
 {
  QHostAddress addr(address);
  tcpSocket->connectToHost(addr, port);
 }
 void Client::read()
  {
      char buffer[1024] = {0};
  tcpSocket->read(buffer, tcpSocket->bytesAvailable());
  cout << buffer << endl;
 status->setText(buffer);
   tcpSocket->close();
  }
 void Client::sendtoser()
  {
    send->setEnabled(true);
status1->setText("connected");
//tcpSocket->close();
//tcpSocket->disconnectFromHost();
  }
void Client::disable()
{
//	send->setEnabled(false);
	status1->setText("disconnected");
}
 void Client::sendto()
 {
QFile f2("./client_log.txt");
f2.open(QIODevice::Append);
QTextStream ot(&f2);
//ot.setVersion(QTextStream::Qt_4_0);

    start("127.0.0.1",18888);
send->setEnabled(false);
status->setText("processing....");
    QString s,c,b,n,a;
   b= l_bid->text();
   s =l_sid->text();
c =l_cid->text();
a =l_amt->text();
n =l_nos->text();
/*if(b==s)
{
	send->setEnabled(true);
	status->setText("seller=buyer");
	return;
}*/

 if( l_bid->text().isEmpty() ||   l_sid->text().isEmpty() || l_cid->text().isEmpty() || l_amt->text().isEmpty() || l_nos->text().isEmpty() )
{
	status->setText("enter all fields ");
	send->setEnabled(true);
}
else if (b!=s)
{

send->setEnabled(false);
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out << (quint16)0;
    out << b<<s<<c<<a<<n;
     out.device()->seek(0);
     out << (quint16)(block.size() - sizeof(quint16));
   cout<<block.size()<<endl;
    tcpSocket->write(block);
send->setEnabled(true);
QTime time;
time=QTime::currentTime();
int min,hr,sec;
min=time.minute();
hr=time.hour();
sec=time.second();
ot<<s<<"|"<<b<<"|"<<c<<"|"<<a<<"|"<<n<<"|"<<hr<<":"<<min<<":"<<sec<<"\n";
f2.close();
l_bid->clear();
l_sid->clear();
l_cid->clear();
l_amt->clear();
l_nos->clear();
}
else
{
        send->setEnabled(true);
        status->setText("seller=buyer");
        return;
}
  }



void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (1) {
  /*  case QAbstractSocket::ServerNotFoundError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    case QAbstractSocket::PeerClosedError:
        break;*/
    case 1:
        QMessageBox::information(this, tr(" Client"),
                                 tr("server not ready :p ") );
    }

    send->setEnabled(true);
}
