#include "topbar.h"
#include "ui_topbar.h"
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QDesktopServices>
TopBar::TopBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopBar)
{


    ui->setupUi(this);
    isPressed = false;


    connect(ui->btnMinium,&QPushButton::clicked,[this]()
    {
        emit miniumWindow();
    });
    connect(ui->btnClose,&QPushButton::clicked,[this]()
    {
        emit closeWindow();
    });


    connect(ui->btnSetting,&QPushButton::clicked,[this]()
    {
       emit showSettingDialog();
    });



    widgetArrs.append(ui->wKujiequ);
    widgetArrs.append(ui->wWechat);
    widgetArrs.append(ui->wWeibo);
    widgetArrs.append(ui->wQQ);
    widgetArrs.append(ui->btnService);




    initBubbleWidget();
    for(int i=0;i<widgetArrs.size();i++)
    {
        widgetArrs.at(i)->installEventFilter(this);
    }
    loadQssFile();


}

//��ʼ���Ի���
void TopBar::initBubbleWidget()
{

    //�����

    QVBoxLayout * vLayout = new QVBoxLayout();
    QPushButton * btn = new QPushButton("ǰ���������ҳ >");
    connect(btn,&QPushButton::clicked,[]()
    {
       QDesktopServices::openUrl(QUrl("https://www.kurobbs.com/mc/home/9"));
    });


    kuJieQu = new BubbleWidget(nullptr,btn);
    kuJieQu->setFixedSize(200,260);

    QLabel * code = new QLabel();
    code->setScaledContents(true);
    code->setPixmap(QPixmap(":/imgs/icons/code.png"));
    QLabel * tip = new QLabel("ɨ�����ؿ����App");

    btn->setStyleSheet("height:50px;font-weight:bold;background-color:#B49F50;color:white;font-size:18px;border-radius:6px;");
    //�ı����� qproperty-alignment:AlignCenter
    tip->setStyleSheet("font-weight:bold;font-size:18px;qproperty-alignment:AlignCenter;");


    vLayout->addWidget(btn);
    vLayout->addWidget(code,0,Qt::AlignCenter);
    vLayout->addWidget(tip);
    kuJieQu->setLayout(vLayout);


    //΢��
    weChat = new BubbleWidget();
    weChat->setFixedSize(210,220);
    vLayout = new QVBoxLayout();
    code = new QLabel();
    code->setScaledContents(true);
    code->setPixmap(QPixmap(":/imgs/icons/wechatCode.png"));
    tip=new QLabel("ɨ���ע΢�Ź��ں�");
    tip->setStyleSheet("font-weight:bold;font-size:18px;qproperty-alignment:AlignCenter;");
    vLayout->addWidget(code,0,Qt::AlignCenter);
    vLayout->addWidget(tip);
    weChat->setLayout(vLayout);




    //΢��

    vLayout = new QVBoxLayout();
    btn = new QPushButton("���ʹٷ�΢�� >");
    connect(btn,&QPushButton::clicked,[]()
    {
        QDesktopServices::openUrl(QUrl("https://weibo.com/u/7730797357?sudaref=mc.kurogame.com"));
    });
    weibo = new BubbleWidget(nullptr,btn);
    weibo->setFixedSize(200,260);

    code = new QLabel();
    code->setScaledContents(true);
    code->setPixmap(QPixmap(":/imgs/icons/weiboCode.png"));
    tip = new QLabel("ɨ���ע�ٷ�΢��");

    btn->setStyleSheet("height:50px;font-weight:bold;background-color:#B49F50;color:white;font-size:18px;border-radius:6px;");
    tip->setStyleSheet("font-weight:bold;font-size:18px;qproperty-alignment:AlignCenter;");

    vLayout->addWidget(btn);
    vLayout->addWidget(code,0,Qt::AlignCenter);
    vLayout->addWidget(tip);
    weibo->setLayout(vLayout);
    //weibo->show();



    //QQ
    QQ = new BubbleWidget();
    QQ->setFixedSize(210,220);


    vLayout = new QVBoxLayout();
    code = new QLabel();
    code->setScaledContents(true);
    code->setPixmap(QPixmap(":/imgs/icons/weiboCode.png"));
    tip=new QLabel("ɨ���QQȺ");
    tip->setStyleSheet("font-weight:bold;font-size:18px;qproperty-alignment:AlignCenter;");
    vLayout->addWidget(code,0,Qt::AlignCenter);
    vLayout->addWidget(tip);
    QQ->setLayout(vLayout);
   // QQ->show();




    //��ϵ�ͷ�
    conService = new BubbleWidget;
    vLayout = new QVBoxLayout();
    tip=new QLabel("��ϵ�ͷ�");
    tip->setStyleSheet("font-weight:bold;font-size:18px;qproperty-alignment:AlignCenter;");

    vLayout->addWidget(tip,0,Qt::AlignCenter);
    vLayout->setContentsMargins(10,20,10,10);
    conService->setLayout(vLayout);
    conService->adjustSize();


    bubbleArrs.append(kuJieQu);
    bubbleArrs.append(weChat);
    bubbleArrs.append(weibo);
    bubbleArrs.append(QQ);
    bubbleArrs.append(conService);

}
TopBar::~TopBar()
{
    delete ui;
}

void TopBar::mousePressEvent(QMouseEvent*event)
{

    if(event->button() == Qt::LeftButton)
    {
        isPressed = true;
        curPos = event->pos();
    }
}
void TopBar::mouseReleaseEvent(QMouseEvent*event)
{

    Q_UNUSED(event);    //ignore warning

    isPressed =false;
}



void TopBar::mouseMoveEvent(QMouseEvent*event)
{

    if(isPressed) //�������������
    {
        emit moveWindow(event->pos()-curPos);
    }
}

void TopBar::paintEvent(QPaintEvent * event)
{

    Q_UNUSED(event);    //ignore warning


    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


    //���ײ�����
    for(int i=0;i<widgetArrs.size()-1;i++)
    {

        if(widgetArrs.at(i)->underMouse())
        {
            QPoint pos = widgetArrs.at(i)->mapToParent(QPoint(0,0));
            QPoint s = pos+QPoint(0,widgetArrs.at(i)->height());    //��ʼ����
            QPoint e = s+QPoint(widgetArrs.at(i)->width(),0);       //��������

            QPen pen;
            pen.setWidth(2);
            pen.setColor(Qt::white);
            p.setPen(pen);
            p.drawLine(s.x()+1,this->height()-1,e.x()-1,this->height()-1);
        }
    }
}


void TopBar::showBubbleWidget(int index)
{


    QPoint p =  widgetArrs.at(index)->mapToGlobal(QPoint(0,0));
    bubbleArrs.at(index)->move(p.x()-bubbleArrs.at(index)->width()/2+widgetArrs.at(index)->width()/2,p.y()+this->height());
    bubbleArrs.at(index)->show();
}

void TopBar::hideBubbleWidget(int index)
{
    bubbleArrs.at(index)->hide();
}
bool TopBar::eventFilter(QObject*obj,QEvent*e)
{


    for(int i =0;i<widgetArrs.size();i++)
    {
        if(widgetArrs.at(i) == obj)
        {
           if(QEvent::Enter == e->type())
           {

               this->setCursor(Qt::PointingHandCursor);
               showBubbleWidget(i);
               return true;
           }
           else if(QEvent::Leave == e->type())
           {



               int y = QCursor::pos().y();
               int by = bubbleArrs.at(i)->y();

               if(qAbs(y-by)<3) //�Ƶ��Ի��򣬲�����
               {
                   break;
               }
               else
               {
                   this->setCursor(Qt::ArrowCursor);
                   hideBubbleWidget(i);
                   return true;
               }

           }
        }
    }


    return QWidget::eventFilter(obj,e);
}

void TopBar::loadQssFile()
{

    QFile f(QString::fromUtf8(":/topbar.css"));
    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&f);

        this->setStyleSheet(ts.readAll());
        f.close();
    }
}




