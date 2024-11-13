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
    ui->lineFilepath->setFocusPolicy(Qt::NoFocus);  //��ֹ��꽹���Զ�ѡ���ı�


    ui->btnSelect->installEventFilter(this);
    ui->lineFilepath->setReadOnly(true);
    QIcon ico(":/imgs/icons/folder.png");
    ui->lineFilepath->addAction(ico, QLineEdit::LeadingPosition);   //QLineEdit ���ͼ��

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


        if(e->type() == QEvent::HoverMove)  //����ƶ�
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
    // ��ȡ�ļ�·���Ĵ洢�豸��Ϣ
    QFileInfo fileInfo(filepath);
    QStorageInfo storageInfo(fileInfo.absolutePath());

    // ��ӡ�����������ÿռ��ʣ��ռ�
    double freeSpace = storageInfo.bytesAvailable() / (1024 * 1024*1024);


    QString info=QString("����ռ䣺%1 ���ÿռ䣺%2GB").arg(needSpace).arg(QString::number(freeSpace,'f',2));

    ui->labelInfo->setText(info);
    ui->lineFilepath->setText(filepath);
    ui->lineFilepath->setCursorPosition(0);  // ���ù���������

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



