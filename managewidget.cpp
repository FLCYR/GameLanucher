#include "managewidget.h"
#include "ui_managewidget.h"
#include <QFileInfo>
#include <QStorageInfo>
#include <QDebug>
#include <QPainter>
ManageWidget::ManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageWidget)
{
    ui->setupUi(this);
    QString appPath = QApplication::applicationFilePath();
    ui->lineFilepath->setFocusPolicy(Qt::NoFocus);  //阻止鼠标焦点自动选择文本


    ui->btnSelect->installEventFilter(this);
    ui->lineFilepath->setReadOnly(true);
    QIcon ico(":/imgs/icons/folder.png");
    ui->lineFilepath->addAction(ico, QLineEdit::LeadingPosition);   //QLineEdit 添加图标

    ui->labelVersion->setStyleSheet("color:white;font-size:16px;font-weight:bold;");
    ui->labelInfo->setStyleSheet("color:white;font-size:16px;font-weight:bold;");
    ui->lineFilepath->setStyleSheet("color:white;height:60px;width:350px;background-color:#373C3E;");
    ui->btnSelect->setStyleSheet("color:black;font-size:20px;height:60px;"
                                 "width:150px;border-radius:3px;background-color:rgba(255,255,255,220);");

    getDiskInfo(appPath);


}

ManageWidget::~ManageWidget()
{
    delete ui;
}


bool ManageWidget::eventFilter(QObject*obj,QEvent*e)
{

    if(obj == ui->btnSelect)
    {


        if(e->type() == QEvent::HoverMove)  //鼠标移动
        {

            this->setCursor(Qt::PointingHandCursor);
            ui->btnSelect->setStyleSheet("color:black;font-size:20px;height:60px;"
                                         "width:150px;border-radius:3px;background-color:rgba(255,255,255,255);");
            return true;
        }
        else if(e->type() == QEvent::HoverLeave)
        {
            this->setCursor(Qt::ArrowCursor);
            ui->btnSelect->setStyleSheet("color:black;font-size:20px;height:60px;"
                                         "width:150px;border-radius:3px;background-color:rgba(255,255,255,220);");

            return true;
        }
    }

    return QWidget::eventFilter(obj,e);   //eventFilter
}

void ManageWidget::getDiskInfo(QString filepath)
{


    QString needSpace = "26.87GB";
    // 获取文件路径的存储设备信息
    QFileInfo fileInfo(filepath);
    QStorageInfo storageInfo(fileInfo.absolutePath());

    // 打印总容量、可用空间和剩余空间
    double freeSpace = storageInfo.bytesAvailable() / (1024 * 1024*1024);


    QString info=QString("所需空间：%1 可用空间：%2GB").arg(needSpace).arg(QString::number(freeSpace,'f',2));

    ui->labelInfo->setText(info);
    ui->lineFilepath->setText(filepath);
    ui->lineFilepath->setCursorPosition(0);  // 设置光标在最左侧

}
void ManageWidget::mouseMoveEvent(QMouseEvent*e)
{

    if(ui->btnSelect->underMouse())
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}



