#include "setting.h"
#include "ui_setting.h"
#include <QDebug>
#include <QListView>
#include <QDesktopServices>
#include <QPen>
#include <QBrush>
Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowMinimizeButtonHint);

    //启用鼠标tracking,
    this->setMouseTracking(true);
    ui->btnLicence->setMouseTracking(true);
    ui->btnPrivacy->setMouseTracking(true);

    ui->radioNoLimit->setChecked(true);
    ui->comLanguage->setView(new QListView());

    connect(ui->btnClose,&QPushButton::clicked,[this]()
    {
        this->close();
    });

    connect(ui->checkExit,&QCheckBox::clicked,[this](bool checked)
    {
        if(checked)
        {
            ui->checkMin->setChecked(false);
        }

    });

    connect(ui->checkMin,&QCheckBox::clicked,[this](bool checked)
    {
        if(checked)
        {
            ui->checkExit->setChecked(false);
        }
    });


    connect(ui->radioLimit,&QRadioButton::clicked,[this](bool checked)
    {
       if(checked)
       {
            ui->lineEdit->setEnabled(true);
       }
    });

    connect(ui->radioNoLimit,&QRadioButton::clicked,[this](bool checked)
    {
       if(checked)
       {
            ui->lineEdit->setEnabled(false);
            ui->lineEdit->clear();
       }
    });


    connect(ui->btnLicence,&QPushButton::clicked,[]()
    {

        QString licUrl = "https://sdk.kurogames.com/p/agreement_public.html";
        QDesktopServices::openUrl(licUrl);
    });

    connect(ui->btnPrivacy,&QPushButton::clicked,[]()
    {

        QString privacy = "https://sdk.kurogames.com/p/personal_privacy.html";
        QDesktopServices::openUrl(privacy);
    });



    connect(ui->btnCancel,&QPushButton::clicked,[this]()
    {
        this->close();
    });

    connect(ui->btnOk,&QPushButton::clicked,[this]()
    {
        //emit
        this->close();
    });



     loadQssFile();

}

Setting::~Setting()
{
    delete ui;
}


void Setting::loadQssFile()
{

    QFile f(QString::fromUtf8(":/setting.css"));
    if (f.open(QIODevice::ReadOnly))
    {

        this->setStyleSheet(f.readAll());
        f.close();
    }
}

void Setting::mousePressEvent(QMouseEvent*event)
{

    if(event->button() == Qt::LeftButton)
    {
        isPressed = true;
        curPos = event->pos();

    }
}
void Setting::mouseReleaseEvent(QMouseEvent*event)
{

    isPressed =false;
}
void Setting::mouseMoveEvent(QMouseEvent*event)
{

    if(isPressed) //鼠标左键按下
    {

        this->move(event->pos()-curPos+this->pos());

    }
    if(ui->btnLicence->underMouse() || ui->btnPrivacy->underMouse())
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void Setting::paintEvent(QPaintEvent*event)
{   


    QPainter p(this);
    QPen pen;
    QPainterPath path;
    pen.setColor(QColor("#CFCFCF"));//CFCFCF
    pen.setWidth(2);
    p.setPen(pen);

    //画顶部线条
    int x = ui->labelSetting->pos().x();
    int y = ui->labelSetting->pos().y()+ui->labelSetting->height()+10;
    p.drawLine(x,y,x+this->width()-40,y);




    //画圆弧
    int aw = 20;
    int endx = x+this->width()-35;
    int endy = y;

    int cx = endx-aw;
    int cy = endy-aw;

    int tx = cx-aw;
    int ty = cy-aw;

    //int bx = cx+aw;
    int by = cy+aw;


    int startAngle = 270;
    int spanAngle = 80;
    double rr = aw;

    int cx1 = tx+aw;
    int cy1 = ty+aw;
    double ex1 = cx1 + rr * cos((startAngle + spanAngle) * 3.14 / 180);
    double ey1 = cy1 - rr * sin((startAngle + spanAngle) * 3.14 / 180);

    startAngle = 90;
    spanAngle  = -80;
    int cx2 = tx+aw;
    int cy2 = by+aw;
    double ex2 = cx2 + rr * cos((startAngle + spanAngle) * 3.14 / 180);
    double ey2 = cy2 - rr * sin((startAngle + spanAngle) * 3.14 / 180);



    p.setBrush(QColor("#333333"));
    p.setPen(Qt::white);
    path.moveTo(cx,by);
    path.lineTo(ex1,ey1);
    path.lineTo(ex2,ey2);
    path.lineTo(cx,by);
    p.drawPath(path);



    path.clear();
    path.moveTo(cx,by);
    QRect r (tx,ty,aw*2,aw*2);  //x,y,width,height
    QRect r2(tx,by,aw*2,aw*2);

    pen.setWidth(1);
    p.setPen(pen);
    p.setRenderHint(QPainter::Antialiasing);
    path.arcTo(r,270,80);
    path.moveTo(cx,by);
    path.arcTo(r2,90,-80);
    p.fillPath(path,Qt::white);



    //画顶部线条
    pen.setColor(QColor("#464646"));
    pen.setWidth(2);
    p.setPen(pen);
    p.drawLine(x+this->width()-35,0,x+this->width()-35,this->height());


    //画右边线条
    int s1x = ui->btnCancel->pos().x();
    int s1y = ui->btnCancel->pos().y()-20;
    int s2x = ui->btnOk->pos().x()+ui->btnOk->width();

    pen.setColor(QColor("#CBCBCB"));
    pen.setWidthF(1.5);
    p.setPen(pen);
    p.drawLine(s1x,s1y,s2x,s1y);


    //画右下角三角形
    QPoint p1(x+this->width()-35,this->height()-10);
    QPoint p2(x+this->width()-35,this->height());
    QPoint p3(x+this->width()-45,this->height());


    QPolygon cons;
    cons<<p1<<p2<<p3;
    p.setPen(Qt::black);
    p.drawPolygon(cons);




}
