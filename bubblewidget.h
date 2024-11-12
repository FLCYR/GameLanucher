#ifndef BUBBLEWIDGET_H
#define BUBBLEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif


QT_BEGIN_NAMESPACE
namespace Ui { class BubbleWidget; }
QT_END_NAMESPACE

class BubbleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BubbleWidget(QWidget *parent = nullptr,QPushButton*_btn=nullptr);
    void initKujiequUI();



protected:

    void paintEvent(QPaintEvent*event);
    void leaveEvent(QEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    bool eventFilter(QObject*obj,QEvent*e);

private:
    Ui::BubbleWidget *ui;

    QPushButton * btn;

signals:

    void hideWindow();

};

#endif // BUBBLEWIDGET_H
