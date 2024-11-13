#include "home.h"
#include "ui_home.h"
#include <QDir>
#include <QDebug>
#include <setting.h>
#include <QStyleOption>
#include <QScreen>
Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    //无边框窗口
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());


    QScreen* screen = QGuiApplication::primaryScreen();

    QRect sRect = screen->availableGeometry();

    this->resize(sRect.width()/1.2, sRect.height()/1.07);
    /*
     * bulletin: 公告栏
     * carousel: 轮播图
     * LoadImage: 窗口背景动图
     * ManageWidget: 下载框
     * setting: 设置对话框
     * topbar: 顶部标题栏
     * bubblewidget: 气泡框
     * home: 主体窗口
     */




    versionNumber = "1.6.4.0";
    slogan.load(":/imgs/image/slogan.png");
    slogan = slogan.scaled(slogan.width()/1.5,slogan.height()/1.5,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    logo.load(":/imgs/image/logo-white.png");
    logo = logo.scaled(logo.width()/6,logo.height()/6,Qt::KeepAspectRatio,Qt::SmoothTransformation);


    loadImage = new LoadImage(this);
    loadImage->setFPS(1000 / 30);//30帧
    loadImage->start();



    connect(loadImage, &LoadImage::sendPixmap, this, &Home::changeBg);
    connect(ui->topBar,&TopBar::miniumWindow,[this]()
    {
        this->showMinimized();
    });
    connect(ui->topBar,&TopBar::closeWindow,[this]()
    {
        this->close();
    });

    connect(ui->topBar,&TopBar::moveWindow,[this](QPoint pos)
    {
        this->move(pos+this->pos());
    });
    connect(ui->topBar,&TopBar::showSettingDialog,[this]()
    {
        Setting st(this);
        st.exec();
    });

    this->setStyleSheet("#topBar{background-color:rgba(0,0,0,80);}");

   // ui->topBar->hide();

   // ui->bulletin->hide();
   // ui->carousel->hide();
   // ui->manage->hide();


}



Home::~Home()
{
    delete ui;
    loadImage->stopThread();
	loadImage->wait();
}


void Home::loadQssFile()
{

    QFile f(QString::fromUtf8(":/style.css"));
    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&f);

        this->setStyleSheet(ts.readAll());
        f.close();
    }
}

void Home::changeBg(QPixmap pix)
{
    bgPixmap = pix.scaled(this->size());
    update();
}
void Home::paintEvent(QPaintEvent* event)
{

    Q_UNUSED(event);

    //绘制背景图
    QPainter p(this);
    p.drawPixmap(0, 0, bgPixmap);


    //绘制logo 和 slogan
    p.drawImage(0,this->height()-slogan.height(),this->slogan);
    p.drawImage(50,120,this->logo);



    //绘制版本号
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::white);
    p.setPen(pen);
    QFont font("Arial", 12, QFont::Bold);
    p.setFont(font);
    p.drawText(10,this->height()-10,versionNumber);
}


