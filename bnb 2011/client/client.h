#include<QtNetwork>
#include<QDialog>

class QDialogButtonBox;
class QTcpSocket;
class QPushButton;
class QLabel;
class QLineEdit;
class QDialogButtonBox;

class Client : public QDialog
{
  Q_OBJECT
  public:
     Client(QWidget *parent = 0);
  private slots:
     void sendto();
     void read();
     void start(QString address, quint16 port);
     void sendtoser();
     void disable();
	void displayError(QAbstractSocket::SocketError socketError);
  private:
    QLabel *bid;
    QLabel *sid;;
    QLabel *cid;
    QLabel *nos;
    QLabel *amt;
    QLineEdit *l_bid;
    QLineEdit *l_sid;
    QLineEdit *l_cid;
    QLineEdit *l_nos;
    QLineEdit *l_amt;
    QPushButton *send;
    QPushButton *quit;

//QPixmap *image;

//QLabel *imageLabel;


    //QPushButton *connect;
    QLabel *status;
    QLabel *status1;
    QTcpSocket *tcpSocket;    
};
