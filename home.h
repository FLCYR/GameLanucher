#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <LoadImage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

    void setFramelessWindow();
    void changeBg(QPixmap pix);

    void loadQssFile();

protected:
    void paintEvent(QPaintEvent *event);


private:
    Ui::Home *ui;
    QPixmap bgPixmap;
    LoadImage* loadImage;
    QImage slogan;
    QImage logo;
    QString versionNumber;

};



#endif // HOME_H
