#include "bubblewidget.h"
#include "ui_bubblewidget.h"
#include <QPainterPath>
#include <QPolygonF>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QDebug>
#include <QDesktopServices>

BubbleWidget::BubbleWidget(QWidget *parent,QPushButton*_btn)
    : QWidget{parent},ui(new Ui::BubbleWidget),btn(_btn)
{

    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    if(btn)
    {
       btn->installEventFilter(this);
    }
}




void BubbleWidget::mouseMoveEvent(QMouseEvent*event)
{


}

bool BubbleWidget::eventFilter(QObject*obj,QEvent*e)
{
    if(btn && obj == btn)
    {
        if(e->type() == QEvent::Enter)
        {
            this->setCursor(Qt::PointingHandCursor);
        }
        else if(e->type() == QEvent::Leave)
        {
            this->setCursor(Qt::ArrowCursor);
        }
    }

    return QWidget::eventFilter(obj,e);

}
void BubbleWidget::leaveEvent(QEvent*event)
{
    this->hide();
}

void BubbleWidget::paintEvent(QPaintEvent*event)
{




    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置背景颜色和边框
    painter.setBrush(Qt::white);
    painter.setPen(QPen(Qt::gray, 1));

    // 创建圆角矩形路径
    QPainterPath path;
    QRectF rect = this->rect().adjusted(1, 10, -1,1); // 为箭头留出空间

    path.addRoundedRect(rect, 6, 6);
    painter.drawPath(path);


    path.clear();
    // 添加三角形箭头
    int arrowWidth = 15;
    int arrowHeight = 6;
    QVector<QPointF>points =
    {
        QPointF(rect.center().x() - arrowWidth / 2, rect.top()),
        QPointF(rect.center().x() + arrowWidth / 2, rect.top()),
        QPointF(rect.center().x(), rect.top() - arrowHeight)
    };
    path.addPolygon(QPolygonF(points));

    // 绘制路径
    painter.drawPath(path);
}
