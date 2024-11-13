#include "bulletin.h"
#include "ui_bulletin.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDesktopServices>
#include <QStyleOption>
Bulletin::Bulletin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bulletin)
{
    ui->setupUi(this);
    loadQssFile();




    ui->btnFirst->installEventFilter(this);
    ui->btnSecond->installEventFilter(this);
    ui->btnThird->installEventFilter(this);

    this->selectBtn = ui->btnFirst;
    connect(ui->btnFirst,&QPushButton::clicked,[this]()
    {
        this->selectBtn = ui->btnFirst;
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->btnSecond,&QPushButton::clicked,[this]()
    {
         ui->stackedWidget->setCurrentIndex(1);
         this->selectBtn = ui->btnSecond;

    });
    connect(ui->btnThird,&QPushButton::clicked,[this]()
    {
         ui->stackedWidget->setCurrentIndex(2);
         this->selectBtn = ui->btnThird;
    });


    QVector<QString>urls;
    urls.append("https://www.kurobbs.com/mc/post/1304494365418856448");
    urls.append("https://www.kurobbs.com/mc/post/1303750756802248704");

    //活动
    QVector<QPair<QString,QString>>activityItems;
    QString s1 = "有奖活动|群星交错|「守岸人」讨论活动启动!";
    QString s1Date = "10-11";
    QString s2 = "《鸣潮》×《中国国家地理》特别合作活动上线!";
    QString s2Date = "10-23";

    activityItems.append(QPair<QString,QString>(s1,s1Date));
    activityItems.append(QPair<QString,QString>(s2,s2Date));

    //公告

    QVector<QPair<QString,QString>>noticeItems;
    QString s3 = "[潮汐觅闻]限时勘察活动——乘霄山特别勘察";
    QString s3Date = "10-30";
    QString s4 = "[浮声沉兵]武器活动唤取——「苍鳞千嶂」概率UP";
    QString s4Date = "10-23";
    noticeItems.append(QPair<QString,QString>(s3,s3Date));
    noticeItems.append(QPair<QString,QString>(s4,s4Date));






    //新闻
    QVector<QPair<QString,QString>>newsItems;
    QString s5 = "《鸣潮》× 中国国家地理特别合作已开启!";
    QString s5Date = "10-27";
    QString s6= "档案公开 | 凝冰造物——釉瑚";
    QString s6Date = "10-21";

    newsItems.append(QPair<QString,QString>(s5,s5Date));
    newsItems.append(QPair<QString,QString>(s6,s6Date));



    addItemContent(activityItems,urls,ui->p1);
    addItemContent(noticeItems,urls,ui->p2);
    addItemContent(newsItems,urls,ui->p3);



}

Bulletin::~Bulletin()
{
    delete ui;
}

void Bulletin::paintEvent(QPaintEvent*e)
{



    QPainter p(this);
    QFontMetrics fm  = selectBtn->fontMetrics();
    QRect r = fm.boundingRect(selectBtn->text());
    int dist = (selectBtn->width()-r.width())/2;
    QPoint p3 = selectBtn->pos();
    int h = selectBtn->height();
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    p.setPen(pen);
    p.drawLine(p3.x()+dist,p3.y()+h,p3.x()+dist+r.width()-1,p3.y()+h);

}

bool Bulletin::eventFilter(QObject*obj,QEvent*e)
{
    if(obj == ui->btnFirst || obj == ui->btnSecond || obj == ui->btnThird)
    {
        if(e->type() == QEvent::Enter)
        {
            this->setCursor(Qt::PointingHandCursor);
            return true;
        }
        else if(e->type() == QEvent::Leave)
        {
            this->setCursor(Qt::ArrowCursor);
        }
    }

    return QWidget::eventFilter(obj,e);

}


void Bulletin::addItemContent(QVector<QPair<QString,QString>>content,QVector<QString>urls,QWidget*win)
{

     QVBoxLayout * lay  = new QVBoxLayout();
     int cnt = 0;
     for(auto item:content)
     {
         InfoWidget*w = new InfoWidget(nullptr,item.first,item.second,urls.at(cnt));

         if(cnt%2==0)
         {
             w->setStyleSheet("background-color:rgba(76,77,83,50);");
         }
         else
         {
             w->setStyleSheet("background-color:rgba(176,177,183,50);");
         }
         lay->addWidget(w);
         cnt++;
     }

     lay->setMargin(0);
     lay->setSpacing(0);
     win->setLayout(lay);


}



void Bulletin::loadQssFile()
{

    QFile f(QString::fromUtf8(":/bulletin.css"));
    if (f.open(QIODevice::ReadOnly))
    {
        qDebug() << "set Qss style success";
        this->setStyleSheet(f.readAll());
        f.close();
    }
}



//-====================



InfoWidget::InfoWidget(QWidget *parent,QString content,QString date,QString _url):QWidget(parent)
{

    url=_url;
    QHBoxLayout * hLayout  = new QHBoxLayout();
    infoLabel = new QLabel(content);
    dateLabel = new QLabel(date);

    infoLabel->setStyleSheet("background-color:rgba(0,0,0,0);font-size:18px;font-weight:bold;color:white;");
    dateLabel->setStyleSheet("background-color:rgba(0,0,0,0);font-size:18px;font-weight:bold;color:white;");



    hLayout->addWidget(infoLabel);
    hLayout->addStretch();
    hLayout->addWidget(dateLabel);
    this->setLayout(hLayout);


    showLine = false;

    this->setMaximumHeight(50);

    bw = new BubbleWidget();
    QVBoxLayout * layout = new QVBoxLayout();
    QLabel * tip = new QLabel(content);
    tip->setStyleSheet("color:black;font-size:18px;font-weight:bold;");
    layout->setContentsMargins(10,20,10,10);
    layout->addWidget(tip);



    bw->setLayout(layout);
    bw->adjustSize();




}
void InfoWidget::paintEvent(QPaintEvent*e)
{

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


    if(showLine)
    {
        int x =infoLabel->pos().x();
        int y = infoLabel->pos().y();

        int h = infoLabel->height();

        QPen pen;
        pen.setColor(QColor("#B99E5E"));
        pen.setWidth(2);
        p.setPen(pen);
        p.drawLine(x-5,y,x-5,y+h);
    }
}

void InfoWidget::leaveEvent(QEvent*e)
{

    showLine = false;
    infoLabel->setStyleSheet("background-color:rgba(0,0,0,0);font-size:18px;font-weight:bold;color:white;");
    dateLabel->setStyleSheet("background-color:rgba(0,0,0,0);font-size:18px;font-weight:bold;color:white;");

    bw->hide();
    update();

}

void InfoWidget::enterEvent(QEvent*e)
{

    showLine = true;
    this->setCursor(Qt::PointingHandCursor);
    infoLabel->setStyleSheet("background-color:rgba(0,0,0,0);font-size:18px;color:rgba(255,255,255,150);font-weight:bold;");
    dateLabel->setStyleSheet("background-color:rgba(0,0,0,0);font-size:18px;color:rgba(255,255,255,150);font-weight:bold;");




    QPoint pos = this->mapToGlobal(QPoint(0,0));
    pos.rx()+=this->width()/2-bw->width()/2;
    pos.ry()+=this->height();
    bw->move(pos);
    bw->show();
    update();



}

void InfoWidget::mousePressEvent(QMouseEvent*e)
{
    if(e->button() == Qt::LeftButton)
    {
         QDesktopServices::openUrl(QUrl(url));
    }

}

InfoWidget::~InfoWidget()
{

}
