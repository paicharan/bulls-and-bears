#include<QtSql>
#include<QDialog>
 #include <QString>
class QDialogButtonBox;
class QPushButton;
class QLabel;
class QLineEdit;

class Client : public QDialog
{
  Q_OBJECT
  public:
     Client(QWidget *parent = 0);
 bool createConnection();
  private slots:
    
     void read();
     
     
     
  private:
    QLabel *cid;
    QLabel *per;
    
    QLineEdit *l_per;
    QLineEdit *l_cid;
    
    QPushButton *send;
   



};
