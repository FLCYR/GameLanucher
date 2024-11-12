#include "LoadImage.h"
#include <QDir>
#include <QApplication>

#include <QDebug>

LoadImage::LoadImage(QObject *parent)
	: QThread(parent)
{
    QDir dir;
    QString imgsDir = QApplication::applicationDirPath() + "/bgs";
    dir.setCurrent(imgsDir);
    QStringList imgList = dir.entryList(QStringList() << "*.jpg", QDir::Files);

    //排序
    //qSort is obsolete.
    std::sort(imgList.begin(), imgList.end(), [](const QString& s1, const QString& s2)
        {
            if (s1.length() == s2.length())
                return s1.toLower() < s2.toLower();
            return s1.length() < s2.length();
        });


    for (auto item : imgList)
    {
        imgNameList.append(imgsDir + "/" + item);
    }

    if(imgList.empty())
    {
        imgNameList.append(":/imgs/image/background.jpg");
    }


    curIndex = 0;
    fps = 33;   //33ms
    stop = false;
}

void LoadImage::setFPS(int fps)
{
	this->fps = fps;
}
void LoadImage::stopThread()
{

    stop = true;
}


//每次加载一张
void LoadImage::run()
{

    while (!stop)
    {
        if (!imgNameList.empty())
        {

            QPixmap pix = QPixmap(imgNameList[curIndex]);

            curIndex = (curIndex + 1) % imgNameList.size();
            emit sendPixmap(pix);
        }
        QThread::msleep(fps);
    }
}
void LoadImage::loadImage()
{

}

LoadImage::~LoadImage()
{

}
