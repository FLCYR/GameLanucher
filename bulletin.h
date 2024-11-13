#ifndef BULLETIN_H
#define BULLETIN_H
#include <QWidget>
#include <QFile>
#include <QMouseEvent>

#include <QPushButton>
#include <QLabel>

#include "bubblewidget.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif


namespace Ui {
class Bulletin;
}





class InfoWidget:public QWidget
{
    Q_OBJECT
public:
     InfoWidget(QWidget *parent = nullptr,QString content="",QString date="",QString _url="");
    ~InfoWidget();
protected:
     void paintEvent(QPaintEvent*e);
     void leaveEvent(QEvent*e);
     void enterEvent(QEvent*e);
     void mousePressEvent(QMouseEvent*e);


private:
     bool showLine;
     QLabel * infoLabel;
     QLabel * dateLabel;
     BubbleWidget * bw;
     QString url;
};



class Bulletin : public QWidget
{
    Q_OBJECT

public:
    explicit Bulletin(QWidget *parent = nullptr);
    ~Bulletin();
    void loadQssFile();


    void addItemContent(QVector<QPair<QString,QString>>content,QVector<QString>urls,QWidget*win);

protected:
    void paintEvent(QPaintEvent*e);
    bool eventFilter(QObject*obj,QEvent*e);

private:
    Ui::Bulletin *ui;
    QPushButton * selectBtn;
};

#endif // BULLETIN_H
