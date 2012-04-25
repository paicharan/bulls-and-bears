#include<QtGui>
#include<QtSql>

class QLabel;

class Server : public QDialog
{
  Q_OBJECT
 public:
   Server (QWidget *parent = 0);
   bool createConnection();
 //public slots:
 
  void read();
 private:
;
  QLabel *status;
  QLabel *ph;
  quint16 blocksize;
}; 
