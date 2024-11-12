#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>
#include <QMouseEvent>
#include "bubblewidget.h"
namespace Ui
{
    class TopBar;
}


class TopBar : public QWidget
{
    Q_OBJECT

public:
    explicit TopBar(QWidget *parent = nullptr);
    ~TopBar();
    void loadQssFile();
    void initBubbleWidget();

    void showBubbleWidget(int index);
    void hideBubbleWidget(int index);
protected:
    void mousePressEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject*obj,QEvent*e);
private:
    Ui::TopBar *ui;
    bool isPressed;
    QPoint curPos;


    QVector<BubbleWidget*> bubbleArrs;
    QVector<QWidget*>widgetArrs;

    BubbleWidget * kuJieQu;
    BubbleWidget * weChat;
    BubbleWidget * weibo;
    BubbleWidget * QQ;

    BubbleWidget * conService;

signals:
    void moveWindow(QPoint pos);
    void miniumWindow();
    void closeWindow();
    void showSettingDialog();
};

#endif // TOPBAR_H
