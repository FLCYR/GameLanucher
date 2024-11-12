#include "carousel.h"
#include "ui_carousel.h"
#include <QDebug>
#include <QDesktopServices>

Carousel::Carousel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Carousel)
{
    ui->setupUi(this);

    nextTimer = new QTimer(this);
    connect(nextTimer,&QTimer::timeout,[this]()
    {

        left = false;
        nextIndex = (curIndex + 1) % imgArr.size();
        animation->start();
    });

    connect(ui->btnLeft,&QPushButton::clicked,[this]()
    {

        nextTimer->stop();
        left = true;
        nextIndex = (curIndex - 1 + imgArr.size()) % imgArr.size();
        animation->start();
    });

    connect(ui->btnRight,&QPushButton::clicked,[this]()
    {

        nextTimer->stop();
        left = false;
        nextIndex = (curIndex + 1) % imgArr.size();
        animation->start();
    });



    imgArr.append(QImage(":/imgs/image/bg1.jpg"));
    imgArr.append(QImage(":/imgs/image/bg2.png"));
    imgArr.append(QImage(":/imgs/image/bg3.jpg"));


    urls.append("https://www.kurobbs.com/mc/home/9");
    urls.append("https://www.bilibili.com/video/BV1UMHsecEAJ/?spm_id_from=333.999.0.0&vd_source=25f16ab79e4f560ba126dd58a02ea2d7");
    urls.append("https://www.bilibili.com/video/BV1Jr421M7C3/?spm_id_from=333.999.0.0&vd_source=25f16ab79e4f560ba126dd58a02ea2d7");

    ui->btnLeft->setStyleSheet("background-color:rgba(0,0,0,80);");
    ui->btnRight->setStyleSheet("background-color:rgba(0,0,0,80);");
    ui->btnRight->hide();
    ui->btnLeft->hide();



   //轮播图效果

   animation = new QPropertyAnimation(this, "offset");
   animation->setStartValue(0.0);
   animation->setEndValue(1.0);
   animation->setDuration(400);
   animation->setEasingCurve(QEasingCurve::OutCubic);   //缓出效果

   curIndex = 0;
   nextIndex = 1;
   offset = 0;
   connect(animation, &QPropertyAnimation::finished, this, [this]()
   {
       curIndex = nextIndex;
       offset = 0.0;
       nextTimer->start(3000);
   });

   nextTimer->start(3000);



}

Carousel::~Carousel()
{
    delete ui;
}

void Carousel::enterEvent(QEvent*e)
{
    ui->btnLeft->show();
    ui->btnRight->show();
    this->setCursor(Qt::PointingHandCursor);

}

void Carousel::leaveEvent(QEvent*e)
{

    ui->btnLeft->hide();
    ui->btnRight->hide();
}


//打开链接
void Carousel::mousePressEvent(QMouseEvent*e)
{

    if(e->button() == Qt::LeftButton)
    {
        QDesktopServices::openUrl(QUrl(urls.at(curIndex)));
    }
}


qreal Carousel::getOffset()
{
    return offset;
}
void Carousel::setOffset(qreal offset)
{
    this->offset=offset;
    update();
}
void Carousel::paintEvent(QPaintEvent*e)
{


    QPainter p(this);
    if(!left)
    {

        p.drawImage(QRect(-width() * offset, 0, width(), height()), imgArr.at(curIndex).scaled(width(),height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        // 绘制下一张图片
        p.drawImage(QRect(width() * (1 - offset), 0, width(), height()), imgArr.at(nextIndex).scaled(width(),height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else
    {
        p.drawImage(QRect(width() * offset, 0, width(), height()), imgArr.at(curIndex).scaled(width(),height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        // 绘制下一张图片
        p.drawImage(QRect(-width() * (1 - offset), 0, width(), height()), imgArr.at(nextIndex).scaled(width(),height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

    }
}

