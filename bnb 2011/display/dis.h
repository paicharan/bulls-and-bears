
#include<QDialog>
#include<QtSql>
class QDialogButtonBox;


class QLabel;
class QLineEdit;
class QDialogButtonBox;

class Dis : public QDialog
{
  Q_OBJECT
  public:
     Dis(QWidget *parent = 0);
 bool createConnection();
 int cc;
  private slots:
     void display();
  private:
QLineEdit *status;
    QLabel *img;
    QLabel *val1;
  QLabel *val2;
 QLabel *val3;
 QLabel *val4;
 QLabel *val5;
 QLabel *val6;
 QLabel *val7;
 QLabel *val8;
 QLabel *val9;
 QLabel *val10; 

 QLabel *val11;
  QLabel *val21;
 QLabel *val31;
 QLabel *val41;
 QLabel *val51;
 QLabel *val61;
 QLabel *val71;
 QLabel *val81;
 QLabel *val91;
 QLabel *val101;

      
};
