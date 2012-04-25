#include<QtNetwork>
#include<QtGui>
#include<QtSql>
class QTcpServer;
class QTcpSocket;
class QLabel;

class Server : public QDialog
{
  Q_OBJECT
 public:
   Server (QWidget *parent = 0);
   bool createConnection();
 public slots:
  void acceptconnection();
  void read();
	void disconnect();
 // void writeto();
 private:
  QTcpServer *server;
  QTcpSocket *socket;
  QLabel *status;
  QLabel *ph;
  quint16 blocksize;
}; 
